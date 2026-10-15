<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests;

use Phalcon\Form\FormFactory;
use Phalcon\Form\FormInterface;
use Phalcon\Form\RequestHandler\NativeRequestHandler;
use Phalcon\Form\Type\Core\FormType;
use Phalcon\Form\Type\Core\SubmitType;
use Phalcon\Form\Type\Core\TextType;
use PHPUnit\Framework\TestCase;

/**
 * Drives NativeRequestHandler through the superglobals. The same scenarios run against
 * HttpRequestHandler in HttpRequestHandlerTest.
 */
class NativeRequestHandlerTest extends TestCase
{
    protected FormFactory $factory;
    private array $server;
    private array $get;
    private array $post;
    private array $files;

    protected function setUp(): void
    {
        $this->factory = new FormFactory();
        $this->server  = $_SERVER;
        $this->get     = $_GET;
        $this->post    = $_POST;
        $this->files   = $_FILES;
        $_GET = $_POST = $_FILES = [];
        unset($_SERVER['REQUEST_METHOD'], $_SERVER['HTTP_X_HTTP_METHOD_OVERRIDE']);
    }

    protected function tearDown(): void
    {
        $_SERVER = $this->server;
        $_GET    = $this->get;
        $_POST   = $this->post;
        $_FILES  = $this->files;
    }

    /** Overridden by HttpRequestHandlerTest to go through a Phalcon request instead. */
    protected function handle(FormInterface $form): void
    {
        (new NativeRequestHandler())->handleRequest($form);
    }

    protected function setRequest(string $method, array $get = [], array $post = [], array $files = [], ?string $override = null): void
    {
        $_SERVER['REQUEST_METHOD'] = $method;
        unset($_SERVER['HTTP_X_HTTP_METHOD_OVERRIDE']);
        if (null !== $override) {
            $_SERVER['HTTP_X_HTTP_METHOD_OVERRIDE'] = $override;
        }
        $_GET   = $get;
        $_POST  = $post;
        $_FILES = $files;
    }

    protected function namedForm(string $method = 'POST', string $name = 'ticket'): FormInterface
    {
        return $this->factory->createNamedBuilder($name, FormType::class, null, ['method' => $method])
            ->add('title', TextType::class)
            ->add('attachment', TextType::class, ['allow_file_upload' => true])
            ->add('save', SubmitType::class)
            ->getForm();
    }

    public function testMethodMismatchDoesNotSubmit(): void
    {
        $this->setRequest('GET', ['ticket' => ['title' => 'x']]);
        $form = $this->namedForm('POST');

        $this->handle($form);

        self::assertFalse($form->isSubmitted());
    }

    public function testNamedFormWithMissingKeyDoesNotSubmit(): void
    {
        $this->setRequest('POST', [], ['other' => ['title' => 'x']]);
        $form = $this->namedForm();

        $this->handle($form);

        self::assertFalse($form->isSubmitted());
    }

    public function testGetNamedFormSubmitsFromQuery(): void
    {
        $this->setRequest('GET', ['ticket' => ['title' => 'from query', 'save' => '']]);
        $form = $this->namedForm('GET');

        $this->handle($form);

        self::assertTrue($form->isSubmitted());
        self::assertSame('from query', $form->get('title')->getData());
        self::assertSame($form->get('save'), $form->getClickedButton());
    }

    public function testPostNamedFormMergesParamsAndFiles(): void
    {
        $this->setRequest('POST', [], ['ticket' => ['title' => 'T']], [
            'ticket' => [
                'name'     => ['attachment' => 'a.txt'],
                'type'     => ['attachment' => 'text/plain'],
                'tmp_name' => ['attachment' => '/tmp/php1'],
                'error'    => ['attachment' => UPLOAD_ERR_OK],
                'size'     => ['attachment' => 3],
            ],
        ]);
        $form = $this->namedForm();

        $this->handle($form);

        self::assertTrue($form->isSubmitted());
        self::assertSame('T', $form->get('title')->getData());
        self::assertEquals(
            ['name' => 'a.txt', 'type' => 'text/plain', 'tmp_name' => '/tmp/php1', 'error' => UPLOAD_ERR_OK, 'size' => 3],
            $form->get('attachment')->getData(),
            'per-attribute $_FILES layout is turned into one array per file'
        );
        self::assertTrue($form->get('attachment')->isSynchronized());
        self::assertNull($form->getClickedButton());
    }

    public function testOnlyFilesStillSubmitsANamedCompoundForm(): void
    {
        $this->setRequest('POST', [], [], [
            'ticket' => [
                'name'     => ['attachment' => 'a.txt', 'title' => ''],
                'type'     => ['attachment' => 'text/plain', 'title' => ''],
                'tmp_name' => ['attachment' => '/tmp/php1', 'title' => ''],
                'error'    => ['attachment' => UPLOAD_ERR_OK, 'title' => UPLOAD_ERR_NO_FILE],
                'size'     => ['attachment' => 3, 'title' => 0],
            ],
        ]);
        $form = $this->namedForm();

        $this->handle($form);

        self::assertTrue($form->isSubmitted(), 'params side defaults to [] for a compound form');
        self::assertSame('a.txt', $form->get('attachment')->getData()['name']);
        self::assertNull($form->get('title')->getData(), 'UPLOAD_ERR_NO_FILE reads as nothing submitted');
    }

    public function testFileUploadIntoAFieldThatDoesNotAllowItIsATransformationFailure(): void
    {
        $this->setRequest('POST', [], [], [
            'ticket' => [
                'name'     => ['title' => 'a.txt'],
                'type'     => ['title' => 'text/plain'],
                'tmp_name' => ['title' => '/tmp/php1'],
                'error'    => ['title' => UPLOAD_ERR_OK],
                'size'     => ['title' => 3],
            ],
        ]);
        $form = $this->namedForm();

        $this->handle($form);

        self::assertTrue($form->isSubmitted());
        self::assertFalse($form->get('title')->isSynchronized());
    }

    public function testPatchKeepsMissingFields(): void
    {
        $this->setRequest('POST', [], ['ticket' => ['title' => 'new']], [], 'PATCH');
        $form = $this->namedForm('PATCH');
        $form->setData(['title' => 'old', 'attachment' => 'keep']);

        $this->handle($form);

        self::assertTrue($form->isSubmitted());
        self::assertSame(['title' => 'new', 'attachment' => 'keep'], $form->getData());
        self::assertFalse($form->get('attachment')->isSubmitted(), 'clearMissing = false');
        self::assertFalse($form->get('save')->isSubmitted());
    }

    public function testMethodOverrideHeaderOnlyAppliesToPost(): void
    {
        $this->setRequest('GET', ['ticket' => ['title' => 'x']], [], [], 'PATCH');
        $form = $this->namedForm('GET');

        $this->handle($form);

        self::assertTrue($form->isSubmitted(), 'override header is ignored for GET');
    }

    public function testUnnamedRootFormNeedsAKnownChildKey(): void
    {
        $this->setRequest('POST', [], ['unrelated' => '1']);
        $form = $this->namedForm('POST', '');

        $this->handle($form);

        self::assertFalse($form->isSubmitted(), 'no known child in $_POST');

        $this->setRequest('POST', [], ['unrelated' => '1', 'title' => 'hello']);
        $form = $this->namedForm('POST', '');

        $this->handle($form);

        self::assertTrue($form->isSubmitted());
        self::assertSame('hello', $form->get('title')->getData());
        self::assertSame(['unrelated' => '1'], $form->getExtraData());
    }

    public function testMethodFieldIsStripped(): void
    {
        $this->setRequest('POST', [], ['title' => 'x', '_method' => 'PUT'], [], 'PUT');
        $form = $this->namedForm('PUT', '');

        $this->handle($form);

        self::assertTrue($form->isSubmitted());
        self::assertSame([], $form->getExtraData(), '_method matching the request method is not extra data');

        // A _method value that differs from the real method is kept as extra data.
        $this->setRequest('POST', [], ['title' => 'x', '_method' => 'DELETE']);
        $form = $this->namedForm('POST', '');

        $this->handle($form);

        self::assertSame(['_method' => 'DELETE'], $form->getExtraData());
    }

    public function testHandleRequestOnTheFormUsesTheConfiguredHandler(): void
    {
        $this->setRequest('POST', [], ['ticket' => ['title' => 'via form']]);
        $form = $this->namedForm();

        $form->handleRequest();

        self::assertTrue($form->isSubmitted());
        self::assertSame('via form', $form->get('title')->getData());
    }
}
