<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests;

use Phalcon\Form\Exception\UnexpectedTypeException;
use Phalcon\Form\FormInterface;
use Phalcon\Form\RequestHandler\HttpRequestHandler;
use Phalcon\Form\Type\Core\FormType;
use Phalcon\Form\Type\Core\TextType;
use Phalcon\Http\Request;

/**
 * Runs every NativeRequestHandlerTest scenario through HttpRequestHandler with a real
 * Phalcon\Http\Request (which reads the same superglobals), plus the Phalcon-specific bits:
 * the flat getUploadedFiles() list and the request service wired into the form config.
 */
final class HttpRequestHandlerTest extends NativeRequestHandlerTest
{
    protected function handle(FormInterface $form): void
    {
        (new HttpRequestHandler())->handleRequest($form, new Request());
    }

    public function testHandleRequestOnTheFormUsesTheConfiguredHandler(): void
    {
        $this->setRequest('POST', [], ['ticket' => ['title' => 'via form']]);
        $form = $this->factory->createNamedBuilder('ticket', FormType::class, null, ['method' => 'POST'])
            ->setRequestHandler(new HttpRequestHandler())
            ->add('title', TextType::class)
            ->getForm();

        $form->handleRequest(new Request());

        self::assertTrue($form->isSubmitted());
        self::assertSame('via form', $form->get('title')->getData());
    }

    public function testRequiresAPhalconRequest(): void
    {
        $form = $this->namedForm();

        $this->expectException(UnexpectedTypeException::class);
        (new HttpRequestHandler())->handleRequest($form, null);
    }

    public function testDeepFileTreeIsRebuiltFromDottedKeys(): void
    {
        $this->setRequest('POST', [], ['ticket' => ['title' => 'T', 'attachments' => ['0' => ['label' => 'first']]]], [
            'ticket' => [
                'name'     => ['attachments' => [['file' => 'a.txt'], ['file' => 'b.txt']], 'cover' => 'c.png', 'none' => ''],
                'type'     => ['attachments' => [['file' => 'text/plain'], ['file' => 'text/plain']], 'cover' => 'image/png', 'none' => ''],
                'tmp_name' => ['attachments' => [['file' => '/tmp/a'], ['file' => '/tmp/b']], 'cover' => '/tmp/c', 'none' => ''],
                'error'    => ['attachments' => [['file' => UPLOAD_ERR_OK], ['file' => UPLOAD_ERR_OK]], 'cover' => UPLOAD_ERR_OK, 'none' => UPLOAD_ERR_NO_FILE],
                'size'     => ['attachments' => [['file' => 1], ['file' => 2]], 'cover' => 3, 'none' => 0],
            ],
        ]);
        $request = new Request();

        $keys = array_map(static fn ($f) => $f->getKey(), $request->getUploadedFiles());
        self::assertSame(['ticket.attachments.0.file', 'ticket.attachments.1.file', 'ticket.cover', 'ticket.none'], $keys, 'Phalcon flattens $_FILES into dot-joined keys');

        $files = HttpRequestHandler::normalizeUploadedFiles($request->getUploadedFiles());

        self::assertSame(
            ['ticket' => [
                'attachments' => [
                    0 => ['file' => ['name' => 'a.txt', 'type' => 'text/plain', 'tmp_name' => '/tmp/a', 'error' => UPLOAD_ERR_OK, 'size' => 1]],
                    1 => ['file' => ['name' => 'b.txt', 'type' => 'text/plain', 'tmp_name' => '/tmp/b', 'error' => UPLOAD_ERR_OK, 'size' => 2]],
                ],
                'cover' => ['name' => 'c.png', 'type' => 'image/png', 'tmp_name' => '/tmp/c', 'error' => UPLOAD_ERR_OK, 'size' => 3],
                'none'  => null,
            ]],
            $files,
            'same shape NativeRequestHandler::fixPhpFilesArray() produces'
        );

        // And the whole thing submits: files merge into the params tree, "none" vanishes.
        $form = $this->factory->createNamedBuilder('ticket')
            ->add('title', TextType::class)
            ->add('attachments', FormType::class)
            ->add('cover', TextType::class, ['allow_file_upload' => true])
            ->add('none', TextType::class)
            ->getForm();
        $form->get('attachments')->add('0', FormType::class);
        $form->get('attachments')->get('0')->add('label', TextType::class)->add('file', TextType::class, ['allow_file_upload' => true]);

        $this->handle($form);

        self::assertTrue($form->isSubmitted());
        self::assertSame('first', $form->getData()['attachments'][0]['label']);
        self::assertSame('a.txt', $form->getData()['attachments'][0]['file']['name']);
        self::assertSame('c.png', $form->getData()['cover']['name']);
        self::assertNull($form->getData()['none']);
        self::assertSame([1 => ['file' => ['name' => 'b.txt', 'type' => 'text/plain', 'tmp_name' => '/tmp/b', 'error' => UPLOAD_ERR_OK, 'size' => 2]]], $form->get('attachments')->getExtraData(), 'no child "1" => extra data');
    }
}
