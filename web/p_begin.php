<?php
Header('Content-Type: text/html; charset=iso-8859-2');
include_once 'p_func.php';
echo '<?xml version="1.0" encoding="iso-8859-2"?>', "\n";
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="cs" lang="CS">

<head>
<meta http-equiv="content-type" content="text/html; charset=iso-8859-2" />
<meta http-equiv="content-language" content="cs" />

<title><?php echo $p_title;?></title>

<meta name="keywords" content="sem, semestralka, woq, basecode, OpenGL, SDL, 3D, terrain" />
<meta name="description" content="Semestrální práce - 3D outdoor střílečka" />
<meta name="author" content="all: Michal Turek; WOQ (zavináč) seznam.cz" />
<meta name="copyright" content="Copyright (c) 2006 Michal Turek" />
<meta name="robots" content="all, follow" />
<meta name="resource-type" content="document" />

<style type="text/css" media="all">@import "style.css";</style>
<style type="text/css" media="print">@import "print.css";</style>
<link href="img/p_ico.png" rel="shortcut icon" type="image/x-icon" />
</head>

<body>
<div id="page">

<!--[if IE ]>
<div style="text-align: center">
<a href="http://firefox.czilla.cz/"><img alt="Mozilla Firefox: Objevte znovu web" title="Mozilla Firefox: Objevte znovu web" style="border:none; width:468px; height:60px;" src="http://firefox.czilla.cz/img/p/cz-ff-468x60-w-objevte.png" /></a>
</div>
<![endif]-->

<div id="main_logo">
<a href="http://woq.nipax.cz/sem"><img src="img/p_logo.jpg" width="640" height="193" alt="sem" /></a>
</div>

<div id="menu">
<?php MenuItem('index', 'Index');?> |
<?php MenuItem('o_news', 'Novinky');?> |
<?php MenuItem('o_license', 'Licence');?> |
<?php MenuItem('o_download', 'Download');?> |
<?php MenuItem('o_ovladani', 'Ovládání');?> |
<?php MenuItem('o_screenshots', 'Screenshoty');?> |
<?php MenuItem('o_classes', 'Třídy');?> |
<?php MenuItem('o_todo', 'TODO');?> |
<?php MenuItem('o_credits', 'Credits');?>

</div>

<div id="main">

<h1><?php echo $p_title;?></h1>
