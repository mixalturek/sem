<?php
// Against spam
function Email($m)
{
	$m = str_replace("@", ' (zavináè) ', $m);
	echo "<span class=\"m\">&lt;$m&gt;</span>";
}

// Insert image
function Img($path, $alt)
{
	if(file_exists($path))
	{
		$path_big = str_replace("_sm", '', $path);
		$img = getimagesize($path);

		if($path != $path_big && file_exists($path_big))// With link to bigger
		{
			echo "<div class=\"img\"><a href=\"$path_big\"><img src=\"$path\" $img[3] alt=\"\" /><br />$alt</a></div>\n";
		}
		else
		{
			echo "<div class=\"img\"><img src=\"$path\" $img[3] alt=\"\" /><br />$alt</div>\n";
		}
	}
}

// Link to web
function Web($addr, $text, $roll = '')
{
	if(file_exists($addr.'.php'))
		echo "<a href=\"$addr.php$roll\">$text</a>";
	else
		echo "<span class=\"invalid_link\">$text</span>";
}

// Link to foreign website
function Blank($addr, $text = '')
{
	if($text)
		echo "<a href=\"$addr\" class=\"blank\" title=\"$addr\">$text</a>";
	else
		echo "<a href=\"$addr\" class=\"blank\">$addr</a>";
}

// Link for download file
function Down($path)
{
	if(file_exists($path))
	{
		$size = filesize($path);

		if(strlen($size) > 6)// MB
			printf("<a href=\"$path\" class=\"down\">%0.1f MB</a>", $size / 1048576);
		else if(strlen($size) > 3)// kB
			printf("<a href=\"$path\" class=\"down\">%0.1f kB</a>", $size / 1024);
		else// B
			echo "<a href=\"$path\" class=\"down\">$size B</a>";
	}
}

function MenuItem($addr, $text)
{
	echo (basename($_SERVER['PHP_SELF']) == "$addr.php")
		? "<span class=\"active\">$text</span>" : Web($addr, $text);
}
?>