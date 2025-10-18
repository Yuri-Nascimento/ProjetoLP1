classDiagram

class Usuarios{
    + id
    + nome
    + login
    + senha
}

class Artista{
    + nome
    + camarim.id
}

class Pedido{
    + id
    + item.id
    + item.nome
    + quantidade
    + camarim.id
    + artista.nome
}

class ListaCompras{
    + id
    + item.id
    + quantidade
    + subtotal
}

class Estoque{
    + item.id
    + item.nome
    + quantidade
}

class Item{
    + id
    + nome
}

class Camarim{
    + id
    + artista.nome
    + item.nome
    + quantidade
}

Artista "2"      --o    "0" Pedido
Artista "0"      o--    "1" Camarim
Pedido "0"       o--    "2" Item
Pedido "0"       o--    "1" Camarim
ListaCompras "0" o--    "2" Item
Estoque "0"      o--    "1" Item
Camarim "0"      o--    "1" Item
