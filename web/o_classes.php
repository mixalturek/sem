<?php
$p_title = 'Tøídy';
include_once 'p_begin.php';
?>

<p>Tøídy jsou programovány co nejobecnìji, tak¾e by nemìl být problém je pou¾ít i v libovolném jiném projektu jako základní kód. Pokud vá¹ projekt nebude dále ¹íøen pod nìkterou z GNU licencí (viz <?php Web('o_license', 'licence');?>) nebo jim kompatibilní, budete moci tento kód pou¾ívat pouze po nahrání z dynamicky linkované knihovny.</p>

<pre>
CApplication			- general application class
	CApplicationEx		- extended application (splash img, fps, fonts)
		CFirstApp	- class of the real application

CMenu				- general menu class
	CSimpleMenu		- rendering of menu

CSceneObject			- general object in the scene
	CCamera			- 3D camera class
	CTerrain		- terrain class
	CBillboard		- textured billboard (object from one quad)
		CBullet		- bullet class for shooting
		CParticle	- class of one particle
		CPlayer		- player class (not whole implemented yet)
	CParticleEngine		- particle engine

CSceneObjectManager		- Objects manager (sorting of transparent objs)
CTextureManager			- texture manager
CImage				- image class (SDL_Image)
CGLExt				- support for OpenGL extensions
CVector				- 3D vector class
CColor				- RGBA color class
CIni				- .INI configuration support
CFont				- text support (SDL_ttf)
CGrid				- objects from lines
CCheat				- cheat class
</pre>

<?php
include_once 'p_end.php';
?>
