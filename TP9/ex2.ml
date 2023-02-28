let rec fold f a l = 
	match l with
	| [] -> a
	| x::q -> f x (fold f a q)
;;

let somme l =
	fold (fun x y -> x + y) 0 l
;;

let recherche l v =
	v = fold (fun x y -> if x = v then x else y) 0 l
;;

let rec concatener a b =
	fold (fun x y -> x::y) b a
;;

let multi_concat l =
	fold concatener [] l
;;

let filter l f =
	fold (fun x y -> if f x then x::y else y) [] l
;;

let map l f =
	fold (fun x y -> f x :: y) [] l
;;

let rec range n =
	if n = 0 then []
	else concatener (range (n-1)) [n-1]
;;

let list_of_string s =
	map (range (String.length s)) (fun i -> s.[i])
;;

let split s ch  =
	let rec split_from_i s sep i curr =
		if i >= String.length s
			then [String.of_seq (List.to_seq curr)]
		else if s.[i] = sep then
			 (String.of_seq (List.to_seq curr))::split_from_i s sep (i + 1) []
		else 
			split_from_i s sep (i + 1) (concatener curr [s.[i]])
	in split_from_i s ch 0 []
;;

let decomp b s =
	assert(b >= 2 && b <= 10);
	let rec decomp_int b x res pow =

		if x <= 0 then res
		else decomp_int b (x / b) (res + pow * (x mod b)) (pow * 10)
		
	in let rec string_to_int_from_i s i res = 
	
		let zero = Char.code '0' in
		let neuf = Char.code '9' in
		
		if (i >= String.length s)
			then (res, i)
		else
			let cr = Char.code s.[i] in
			if cr < zero || cr > neuf
				then (res, i)
			else
				string_to_int_from_i s (i + 1) (res * 10 + cr - zero)
				
	in let x,y = string_to_int_from_i s 0 0 in
	(decomp_int b x 0 1, y)

		

let test() =
	assert (somme [4; 5; 19] = 28);
	assert (concatener [3; 8] [9; 12] = [3; 8; 9; 12]);
	assert (multi_concat [[4; 8]; [2; 6]; [1; 3; 5]] =[4; 8; 2; 6; 1; 3; 5]);
	assert (range 5 = [0; 1; 2; 3; 4]);
	assert (filter (range 10) (fun n -> n mod 3 = 0) = [0; 3; 6; 9]);
	assert (map (range 5) (fun n -> n mod 3) = [0; 1; 2; 0; 1]);
	
	assert (list_of_string "test" = ['t'; 'e'; 's'; 't']);
	assert (split "MP2 tous des dieux" ' ' = ["MP2"; "tous"; "des"; "dieux"]);
	assert (decomp 10 "56+32" = (56, 2));
	assert (decomp 2 "254" = (11111110, 3));
	
	print_string "Tous les tests ont reussi."
;;

