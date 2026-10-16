<?php switch ($username): ?>
<?php case 'Jim': ?>
Hello username
<?php case 'Nik': ?>
<?= $username ?>!
<?php break; ?>
<?php default: ?>
Who are you?
<?php endswitch ?>
