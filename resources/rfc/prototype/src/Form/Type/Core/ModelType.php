<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

use Phalcon\Form\ChoiceList\ModelChoiceLoader;
use Phalcon\Form\ChoiceList\ModelIdReader;
use Phalcon\Form\Options\InvalidOptionsException;
use Phalcon\Form\Options\Options;
use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\Type\AbstractType;
use Phalcon\Mvc\ModelInterface;

/**
 * A ChoiceType whose choices are the rows of a Phalcon\Mvc\Model: the <select> lists
 * Model::find($parameters), the option values are the primary keys and the form data is the
 * model instance (or an array of instances with "multiple").
 *
 *   'class'        required, the model FQCN
 *   'parameters'   the Model::find() argument (conditions/bind/order... array or a conditions
 *                  string), or a Closure returning it, evaluated when the list is first needed
 *   'choice_label' attribute or getter name, callable, or null to use the model's __toString()
 *                  (the old Select element's `using[1]`)
 *   'choice_value' defaults to the primary key read from the models metadata (`using[0]`);
 *                  an attribute name or callable overrides it
 *   'choices'      a Resultset or array of models given directly instead of running find()
 *   group_by, preferred_choices, placeholder, multiple, expanded... as in ChoiceType
 *
 * Behaviour: the list is loaded lazily (no query until an option list or an unknown value is
 * needed); a preselected model is matched by primary key, not identity, so a related record
 * selects its option whichever query produced it; a submitted key loads that row alone when the
 * list has not been loaded yet (see ModelChoiceLoader); an unknown key makes the form not
 * synchronized (single) or adds an error (multiple), like ChoiceType.
 *
 * Replaces Phalcon\Forms\Element\Select with a ResultsetData + `using` pair.
 * Counterpart of Symfony's EntityType (Doctrine bridge).
 *
 * prototype: no "query result cache", no "em"/"query_builder" (parameters covers it), the
 * "class" model must be constructible with the default DI (Di::getDefault()).
 */
final class ModelType extends AbstractType
{
    public function configureOptions(OptionsResolver $resolver): void
    {
        $idReader = static fn (Options $options): ModelIdReader => new ModelIdReader($options['class']);

        $choiceLoader = static function (Options $options): ?ModelChoiceLoader {
            if (null !== $options['choices']) {
                return null; // a Resultset/array of models was given: no query of our own
            }

            $value = $options['choice_value'];

            return new ModelChoiceLoader(
                $options['class'],
                $options['parameters'],
                $value instanceof ModelIdReader || is_string($value) ? $value : null,
            );
        };

        $choiceLabel = static function (Options $options): \Closure {
            if (!method_exists($options['class'], '__toString')) {
                throw new InvalidOptionsException(sprintf('The "choice_label" option is required because "%s" has no __toString() method.', $options['class']));
            }

            return static fn (mixed $model): string => (string) $model;
        };

        $resolver->setRequired('class');
        $resolver->setDefaults([
            'parameters'    => null,
            'choices'       => null,
            'choice_loader' => $choiceLoader,
            'choice_value'  => $idReader,
            'choice_label'  => $choiceLabel,
        ]);

        $resolver->setAllowedTypes('class', 'string');
        $resolver->setAllowedTypes('parameters', ['null', 'array', 'string', 'callable']);

        $resolver->setNormalizer('class', static function (Options $options, string $class): string {
            if (!is_a($class, ModelInterface::class, true)) {
                throw new InvalidOptionsException(sprintf('The "class" option must be a %s, "%s" given.', ModelInterface::class, $class));
            }

            return $class;
        });
    }

    public function getParent(): ?string
    {
        return ChoiceType::class;
    }

    public function getBlockPrefix(): string
    {
        return 'model';
    }
}
