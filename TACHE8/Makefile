#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2020/2021
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond à toutes les dépendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'édition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
# EXECUTABLES = test_image test_geom2d
EXECUTABLES = test_simplification_contour_segment test_simplification_contour_bezier2 test_simplification_contour_bezier3

#############################################################################
# definition des regles
#############################################################################

########################################################
# la règle par défaut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $< -lm

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
image.o : image.c image.h types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $< -lm

test_image.o : test_image.c image.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $< -lm

test_geom2d.o: test_geom2d.c types.h
	$(CC) -c $< -lm

geom2d.o: geom2d.c geom2d.h
	$(CC) -c $< -lm

test_contour.o: test_contour.c types.h image.h
	$(CC) -c $< -lm

sequence_point.o: sequence_point.c types.h
	$(CC) -c $< -lm

simplification_contour.o: simplification_contour.c simplification_contour.h
	$(CC) -c $< -lm	


########################################################
# regles explicites de creation des executables

test_image : test_image.o image.o 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@ -lm

test_geom2d: geom2d.o test_geom2d.o
	clang $^ -o $@ -lm

test_contour: contour.o test_contour.o image.o sequence_point.o
	clang $^ -o $@ -lm
	
test_simplification_contour_bezier2: test_simplification_contour_bezier2.o geom2d.o sequence_point.o image.o contour.o simplification_contour.o
	clang $^ -o $@ -lm

test_simplification_contour_bezier3: test_simplification_contour_bezier3.o geom2d.o sequence_point.o image.o contour.o simplification_contour.o
	clang $^ -o $@ -lm

prog-test: prog-test.o simplification_contour.o geom2d.o sequence_point.o image.o contour.o
	clang $^ -o $@ -lm

test_simplification_contour_segment: test_simplification_contour_segment.o geom2d.o sequence_point.o image.o contour.o simplification_contour.o
	clang $^ -o $@ -lm

# regle pour "nettoyer" le répertoire
clean:
	rm -fR $(EXECUTABLES) output.pbm *.o 
