# Spécificitée

- `echo test > test1 test2 > test3` -> Write "test test2" dans `test1` ET `test3`
- `cat Makefile > test5 | echo` -> Doit afficher
	```

	```
	et le fichier test5 est créé mais est vide
- `ls Makefile > test4 | echo "yo"` -> Doit afficher
	```
		yo
		zsh: permission denied: test4
	```
