TARGET		= sem
CC		= g++
CFLAGS		= -Wall $(shell sdl-config --cflags)
LDFLAGS		= -L/usr/X11R6/lib $(shell sdl-config --libs) -lSDL_image -lSDL_ttf -lGL -lGLU -lm
OBJECTS		= $(shell ls *.cpp | sed 's/.cpp/.o/')


.PHONY: depend
.PHONY: run
.PHONY: clean
.PHONY: lines
#.PHONY: install


%.o: %.cpp
	$(CC) -c $< $(CFLAGS)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

# Mozna bude nadavat kvuliva STL a SDL hlavickam, ale je to OK
depend:
	makedepend $(shell ls *.cpp)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o core

# ;-)
lines:
	cat *.h *.cpp | wc -l


# DO NOT DELETE

capplication.o: capplication.h basecode.h usereventcodes.h cini.h
capplicationex.o: capplicationex.h basecode.h usereventcodes.h capplication.h
capplicationex.o: cini.h cfont.h cimage.h
cbillboard.o: cbillboard.h basecode.h usereventcodes.h cvector.h
cbillboard.o: csceneobject.h ctexturemanager.h cimage.h ccolor.h
cbullet.o: cbullet.h basecode.h usereventcodes.h cbillboard.h cvector.h
cbullet.o: csceneobject.h ctexturemanager.h cimage.h ccolor.h
ccamera.o: ccamera.h basecode.h usereventcodes.h cvector.h csceneobject.h
ccamera.o: ctexturemanager.h cimage.h
ccolor.o: ccolor.h basecode.h usereventcodes.h
cfirstapp.o: cfirstapp.h basecode.h usereventcodes.h capplicationex.h
cfirstapp.o: capplication.h cini.h cfont.h cimage.h cterrain.h csceneobject.h
cfirstapp.o: cvector.h ctexturemanager.h cglext.h cgrid.h ccheat.h
cfirstapp.o: csimplemenu.h cmenu.h ccamera.h csceneobjectmanager.h cbullet.h
cfirstapp.o: cbillboard.h ccolor.h cparticleengine.h cparticle.h cplayer.h
cfont.o: cfont.h basecode.h usereventcodes.h cimage.h
cglext.o: cglext.h basecode.h usereventcodes.h
cgrid.o: cgrid.h basecode.h usereventcodes.h
ccheat.o: ccheat.h basecode.h usereventcodes.h
cimage.o: cimage.h basecode.h usereventcodes.h
cini.o: cini.h basecode.h usereventcodes.h
cmenu.o: cmenu.h basecode.h usereventcodes.h
cparticle.o: cparticle.h basecode.h usereventcodes.h cvector.h ccolor.h
cparticle.o: cbillboard.h csceneobject.h ctexturemanager.h cimage.h
cparticleengine.o: cparticleengine.h basecode.h usereventcodes.h cvector.h
cparticleengine.o: ccolor.h csceneobject.h ctexturemanager.h cimage.h
cparticleengine.o: cparticle.h cbillboard.h
cplayer.o: cplayer.h basecode.h usereventcodes.h cbillboard.h cvector.h
cplayer.o: csceneobject.h ctexturemanager.h cimage.h ccolor.h
csceneobject.o: csceneobject.h basecode.h usereventcodes.h cvector.h
csceneobject.o: ctexturemanager.h cimage.h
csceneobjectmanager.o: csceneobjectmanager.h basecode.h usereventcodes.h
csceneobjectmanager.o: csceneobject.h cvector.h ctexturemanager.h cimage.h
csimplemenu.o: csimplemenu.h basecode.h usereventcodes.h cmenu.h cfont.h
csimplemenu.o: cimage.h
cterrain.o: cterrain.h basecode.h usereventcodes.h cimage.h cini.h
cterrain.o: csceneobject.h cvector.h ctexturemanager.h cglext.h
ctexturemanager.o: ctexturemanager.h basecode.h usereventcodes.h cimage.h
cvector.o: cvector.h basecode.h usereventcodes.h
main.o: basecode.h usereventcodes.h cfirstapp.h capplicationex.h
main.o: capplication.h cini.h cfont.h cimage.h cterrain.h csceneobject.h
main.o: cvector.h ctexturemanager.h cglext.h cgrid.h ccheat.h csimplemenu.h
main.o: cmenu.h ccamera.h csceneobjectmanager.h cbullet.h cbillboard.h
main.o: ccolor.h cparticleengine.h cparticle.h cplayer.h
