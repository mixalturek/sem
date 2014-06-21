<?php
/*
$message = Date('d.m.Y - H:i:s')." - '{$_POST['search']}'\n";
error_log($message, 3, FULLTEXTLOGFILE);// Ulo¾í do logù
*/

Header("Location: http://www.google.com/search?q=site:woq.nipax.cz/sem {$_POST['search']}&ie=ISO-8859-2");
exit;
?>
