<?php
$p_title = 'Hra `sem`';
include_once 'p_begin.php';
?>


<p>Aplikace pøedstavuje hru ve stylu klasického Scorche nebo Wormsù. Zatím umo¾òuje pouze chození po vý¹kových mapách a støílení vèetnì kolizí s terénem a výbuchy. Hra je napsána v programovacím jazyce C++ (èistý OOP), vyu¾ívá knihoven STL (standardní knihovna C++), <?php Blank('http://www.libsdl.org/', 'SDL');?> (aplikaèní kód), <?php Blank('http://www.libsdl.org/projects/SDL_image/', 'SDL_image');?> (nahrávání obrázkù), <?php Blank('http://www.libsdl.org/projects/SDL_ttf/', 'SDL_ttf');?> (zobrazování textù) a <?php Blank('http://www.opengl.org/', 'OpenGL');?> (rendering). Aplikace je také je pøipravena pro pou¾ití <?php Blank('http://www.gnu.org/software/gettext/', 'gettextu');?> (jazykové mutace), ten v¹ak je¹tì nebyl napojen.</p>


<h3>Systémové po¾adavky, instalace, spu¹tìní...</h3>

<p>Aplikace je vyvíjena pod systémy Debian Sarge GNU/Linux, Mandrakelinux 10.0 a Mandrakelinux 10.1 a byla testována pod MS Windows XP, MS Windows 2000 (emulace ve VMware) a MacOs X. Teoreticky by mìla fungovat v¹ude tam, kde SDL (BeOS, MacOS Classic, FreeBSD, OpenBSD, BSD/OS, Solaris, IRIX, QNX, Windows CE, AmigaOS, Dreamcast, Atari, NetBSD, AIX, OSF/Tru64, SymbianOS), ale z dùvodu nedostupnosti nebyly tyto systémy a platformy testovány.</p>

<p>V systému by mìly být nainstalovány ovladaèe grafické karty nebo alespoò Mesa pro sorfwarový rendering. Testy byly provádìny na grafických kartách nVIDIA GeForce4 MX, nVIDIA GeForce2 MX a ATI Radeon 7000. Dále by mìly být v systému pøítomné (devel!!!) balíèky knihoven <?php Blank('http://www.libsdl.org/', 'SDL');?>, <?php Blank('http://www.libsdl.org/projects/SDL_image/', 'SDL_image');?> a <?php Blank('http://www.libsdl.org/projects/SDL_ttf/', 'SDL_ttf');?>, jinak kompilace skonèí chybou.</p>


<?php
include_once 'p_end.php';
?>
