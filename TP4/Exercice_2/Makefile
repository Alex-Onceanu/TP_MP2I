APP=exec

$(APP):main.c piece.c etage.c maison.c utility.c quartier.c ville.c
	gcc -o $@ $^

clean:
	-rm -f $(APP)