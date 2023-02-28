let rec recherche l v =
	match l with
	| [] -> false
	| h::t -> if h = v then true else recherche t v
;;

let rec somme l =
	match l with
	| [] -> 0
	| h::t -> h + somme t
;;

let plus_grand a b = if a > b then a else b;;

let rec max l =
	match l with
	| [] -> failwith "Liste vide"
	| x::[] -> x
	| h::t -> plus_grand h (max t)
;;

let rec concatener a b =
	match a with 
	| [] -> b
	| x::y -> x::(concatener y b)
;;

let rec multi_concat l =
	match l with
	| [] -> []
	| x::y -> concatener x (multi_concat y)
;;

let rec map l f =
	match l with
	| [] -> []
	| x::y -> f x::map y f
;;

let rec fib n =
	match n with
	| 0 -> 0
	| 1 -> 1
	| _ -> fib (n-1) + fib (n-2)
;;

let rec range n =
	match n with
	| 0 -> []
	| _ -> concatener (range (n-1)) [n-1]
;;

let rec make_list f n = map (range n) f;;

let rec compose_liste l =
	match l with
	| [] -> failwith "Mauvaise utilisation, il faut composer des fonctions."
	| h::[] -> h
	| f::t -> (fun x -> f ((compose_liste t) x))
;;	

let petit_f k x =
	if x mod (2 + k) = 0 then x / (2 + k)
	else 3 * x + k
;;

let grand_f n =
	let cmp = compose_liste (make_list petit_f n)
	in somme (make_list cmp n)
;;

let test() =
	assert (somme [4; 5; 19] = 28);
	assert (max [6; 9; 12; 0; -5; 3] = 12);
	assert (concatener [3; 8] [9; 12] = [3; 8; 9; 12]);
	assert (multi_concat [[4; 8]; [2; 6]; [1; 3; 5]] =[4; 8; 2; 6; 1; 3; 5]);
	assert (range 5 = [0; 1; 2; 3; 4]);
	assert (make_list fib 8 = [0; 1; 1; 2; 3; 5; 8; 13]);
	
	print_string "Tous les tests ont reussi."
;;





