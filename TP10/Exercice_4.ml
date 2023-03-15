let int_of_bool b = if b then 1 else 0

let cherche_plus_long (l : string list) : string =
  let rec aux (l : string list) (max_len : int) (res : string) : string =
    match l with
    | [] -> res
    | h :: t ->
        let tmp = String.length h in
        if tmp > max_len then aux t tmp h else aux t max_len res
  in
  aux l 0 ""
;;

(* _______________________________________________________________*)

type pre_tree = Node of (bool * (char * pre_tree) list)

let t =
  Node
    ( false,
      [
        ('t', Node (true, [ ('r', Node (false, [ ('o', Node (true, [])) ])) ]));
        ('f', Node (false, [ ('o', Node (true, [])) ]));
      ] )
;;

(* Il suffit de compter le nombre de noeuds 'V' *)
let rec taille (Node (b, l) : pre_tree) : int =
  match l with
  | [] -> int_of_bool b
  | (c, a) :: t -> taille a + taille (Node (b, t))
;;

let liste_tous_les_mots (arb : pre_tree) : string list =
  let rec aux (Node (b, l) : pre_tree) (actuel : char list) : string list =
    match l with
    | [] -> if b then [ String.of_seq (List.to_seq (List.rev actuel)) ] else []
    | (c, a) :: t -> aux a (c :: actuel) @ aux (Node (b, t)) actuel
  in
  aux arb []
;;

let plus_long (a : pre_tree) : int =
  String.length (cherche_plus_long (liste_tous_les_mots a))
;;

let rechercher (s : string) (a : pre_tree) : bool =
  List.mem s (liste_tous_les_mots a)
;;

(* Renvoie un pre_tree de type "colonne" formant comme unique mot s *)
let rec tree_of_string (s : string) : pre_tree =
  if String.length s = 0 then Node (true, [])
  else
    Node
      (false, [ (s.[0], tree_of_string (String.sub s 1 (String.length s - 1))) ])
;;

let ajouter (s : string) (Node (arbb, arbl) : pre_tree) : pre_tree =
  (* ajoute s à une liste d'aretes de pre_tree *)
  let rec aux (s : string) (l : (char * pre_tree) list) : (char * pre_tree) list
      =
    if String.length s = 0 then []
    else
      let suiv = String.sub s 1 (String.length s - 1) in
      match l with
      | [] -> [ (s.[0], tree_of_string suiv) ]
      | (c, Node (ab, al)) :: t ->
          if c = s.[0] then (c, Node (ab, aux suiv al)) :: t
          else (c, Node (ab, al)) :: aux s t
  in
  Node (arbb, aux s arbl)
;;

let construire (a : pre_tree) : pre_tree =
  let rec aux (a : pre_tree) (l : string list) : pre_tree =
    match l with
    | [] -> a
    | h :: t -> aux (ajouter h a) t
  in
  aux a (String.split_on_char ' ' (read_line ()))
;;

let compare (a : char * pre_tree) (b : char * pre_tree) : int =
  let a1, _ = a in
  let b1, _ = b in
  if a1 < b1 then -1 else if a1 = b1 then 0 else 1
;;

let rec sec (l : ('a * 'b) list) : 'b list =
  match l with
  | [] -> []
  | (g, d) :: q -> d :: sec q
;;

let rec compose a b =
  match (a, b) with
  | [], [] -> []
  | (ax, _) :: aq, bx :: bq -> (ax, bx) :: compose aq bq
  | _, _ -> failwith "non"
;;

let rec normalize (Node (ab, al) : pre_tree) : pre_tree =
  match al with
  | [] -> Node (ab, [])
  | _ ->
      let nouv_al = List.map normalize (sec al) in
      Node (ab, List.sort compare (compose al nouv_al))
;;

let enumerer (a : pre_tree) : string list = liste_tous_les_mots a

let enumerer_prefixe (s : string) (a : pre_tree) : string list =
  List.filter (String.starts_with ~prefix:s) (enumerer a)
;;

let fusion (a : pre_tree) (b : pre_tree) : pre_tree =
  let rec aux (a : pre_tree) (l : string list) : pre_tree =
    match l with
    | [] -> a
    | h :: t -> if rechercher h a then aux a t else aux (ajouter h a) t
  in
  aux a (enumerer b)
;;

let t2 =
  Node
    ( false,
      [
        ( 'b',
          Node
            ( false,
              [
                ( 'o',
                  Node
                    ( false,
                      [
                        ('r', Node (true, []));
                        ('n', Node (false, [ ('d', Node (true, [])) ]));
                      ] ) );
                ('m', Node (true, []));
              ] ) );
        ('t', Node (false, [ ('r', Node (false, [ ('o', Node (true, [])) ])) ]));
      ] )
;;

let test () =
  assert (taille t = 3);
  assert (plus_long t = 3);
  assert (rechercher "fo" t);
  assert (liste_tous_les_mots (ajouter "fils" t) = [ "tro"; "t"; "fo"; "fils" ]);

  (* assert (enumerer_prefixe "t" t = [ "t"; "tro" ]);
     assert (enumerer (fusion t t2) = [ "bm"; "bond"; "bor"; "fo"; "t"; "tro" ]); *)
  print_string "Fin des tests."
;;

test ()
