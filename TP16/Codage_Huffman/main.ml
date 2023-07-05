type huffman = Leaf of int * char | Node of int * huffman * huffman

let freq (h : huffman) : int =
  match h with
  | Leaf (x, _) | Node (x, _, _) -> x
;;

let fusion (h1 : huffman) (h2 : huffman) : huffman =
  Node (freq h1 + freq h2, h1, h2)
;;

let count_freqs (s : string) : (char, int) Hashtbl.t =
  let (res : (char, int) Hashtbl.t) = Hashtbl.create 128 in
  for i = 0 to String.length s - 1 do
    Hashtbl.replace res s.[i]
      (1 + if Hashtbl.mem res s.[i] then Hashtbl.find res s.[i] else 0)
  done;
  res
;;

let huffman_leaves (s : string) : huffman list =
  Hashtbl.fold (fun k v q -> Leaf (v, k) :: q) (count_freqs s) []
;;

let separer (l : 'a list) : 'a list * 'a list =
  let rec alterne (l : 'a list) (l1 : 'a list) (l2 : 'a list) :
      'a list * 'a list =
    match l with
    | [] -> (l1, l2)
    | h :: t -> alterne t (h :: l2) l1
  in
  alterne l [] []
;;

let rec merge (l1 : 'a list) (l2 : 'a list) (cmp : 'a -> 'a -> bool) : 'a list =
  match (l1, l2) with
  | [], l | l, [] -> l
  | h1 :: t1, h2 :: t2 ->
      if cmp h1 h2 then h1 :: merge t1 l2 cmp else h2 :: merge l1 t2 cmp
;;

let rec merge_sort (l : huffman list) : huffman list =
  match l with
  | [] -> []
  | h :: [] -> [ h ]
  | _ ->
      let g, d = separer l in
      merge (merge_sort g) (merge_sort d) (fun a b -> freq a < freq b)
;;

let rec insert_huffman (h : huffman) (l : huffman list) : huffman list =
  match l with
  | [] -> [ h ]
  | x :: q -> if freq x < freq h then x :: insert_huffman h q else h :: l
;;

let rec fuse_list (l : huffman list) : huffman =
  match l with
  | [] -> failwith "liste vide"
  | h :: [] -> h
  | h1 :: h2 :: l -> fuse_list (insert_huffman (fusion h1 h2) l)
;;

(* Complexité : O(n^2) pire cas (où n = |s|) *)
let huffman_tree (s : string) : huffman =
  fuse_list (merge_sort (huffman_leaves s))
;;

let rec build_path_table (tab : (char, bool list) Hashtbl.t) (h : huffman)
    (acc : bool list) : unit =
  match h with
  | Leaf (_, c) -> Hashtbl.replace tab c (List.rev acc)
  | Node (_, g, d) -> begin
      build_path_table tab g (false :: acc);
      build_path_table tab d (true :: acc)
    end
;;

let encode (s : string) (tab : (char, bool list) Hashtbl.t) : bool list =
  let rec prochaine_lettre (s : string) (i : int) (n : int) (acc : bool list) :
      bool list =
    if i >= n then acc
    else prochaine_lettre s (i + 1) n (Hashtbl.find tab s.[i] @ acc)
  in
  List.rev (prochaine_lettre s 0 (String.length s - 1) [])
;;

let compression_huffman (s : string) : bool list * huffman =
  let h = huffman_tree s in
  let (tab : (char, bool list) Hashtbl.t) = Hashtbl.create 128 in
  build_path_table tab h [];

  (encode s tab, h)
;;

(* Pour vingt_mille_lieues.txt :
     Huffman : 4077647
      p : 96
      Pas d'encodage : 6320230
      Ratio : 0.645173830699 *)
let compare (s : string) : unit =
  let l, h = compression_huffman s in
  let t = Hashtbl.create 128 in
  build_path_table t h [];
  let p = Hashtbl.length t in
  let n1 = List.length l in
  let n2 =
    (1 + Float.to_int (log (Int.to_float p) /. log 2.)) * String.length s
  in

  print_string "Huffman : ";
  print_int n1;
  print_newline ();

  print_string "p :";
  print_int p;
  print_newline ();

  print_string "Pas d'encodage : ";
  print_int n2;
  print_newline ();

  print_string "Ratio : ";
  print_float (Int.to_float n1 /. Int.to_float n2);
  print_newline ()
;;

let read_file (filename : string) : string =
  let rec read_line (f : in_channel) (acc : string list) : string =
    try
      let ligne = input_line f in
      read_line f (ligne :: acc)
    with
    | End_of_file -> String.concat "\n" (List.rev acc)
    | _ -> failwith "autre erreur"
  in
  read_line (open_in filename) []
;;

let rec read_path (h : huffman) (l : bool list) : char * bool list =
  match (l, h) with
  | [], _ -> ('|', [])
  | x :: q, Leaf (n, c) -> (c, l)
  | x :: q, Node (v, g, d) -> if x then read_path d q else read_path g q
;;

let rec decompression_huffman (h : huffman) (l : bool list) : string =
  let c, l2 = read_path h l in
  if List.length l = 0 then "" else String.make 1 c ^ decompression_huffman h l2
;;
