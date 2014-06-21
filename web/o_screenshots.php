<?php
$p_title = 'Screenshoty';
include_once 'p_begin.php';

echo '<hr /><h3>sem 0.4</h3>';

for($i = 0; $i < 3; $i++)
{
	Img("img/screenshots/sem_0.4_{$i}_sm.png", "Screenshot #$i");
}

echo '<hr /><h3>sem 0.3</h3>';

Img('img/lin_sm.jpg', 'Debian Sarge GNU/Linux (správce oken PekWM)');
Img('img/win_sm.jpg', 'Microsoft Windows XP');
Img('img/mac_sm.jpg', 'MacOs X');
Img('img/sol_sm.jpg', 'Sun Solaris s CDE (ssh na Debian a emulace Windows :o)');

include_once 'p_end.php';
?>
