#TP Reseaux : routage

#### Zakaria EL KHAYARI

## 1 Routage statique

#### 1) Affichez la table de routage des routeurs. Que constatez-vous ?

```console
$ ip route
```

On constate qu'il y n'existe pas de routage, cela est normal car les routeurs viennent d'être créés.

#### 2) Configurez et activez les interfaces des routeurs en vous basant sur l’adressage IPv4 vu en TD. Comment vérifier que la configuration IP est correcte ?

On commence par activer les interfaces des routeurs :

```console
$ ip link set dev <interface> up
```

Puis on procéde à l'adressage avec la commande :

```console
ip address add dev <interface> <address_ip/masque>
```

Adressage IPv4 vu en TD:

-   **R1** :

```console
$ ip addr add dev eth1 211.230.193.197/30
$ ip addr add dev eth0 211.230.193.193/30
```

-   **R2** :

```console
$ ip addr add dev eth1 211.230.193.194/30
$ ip addr add dev eth0 211.230.193.1/25
```

-   **R3** :

```console
$ ip addr add dev eth0 211.230.193.198/30
$ ip addr add dev eth1 211.230.193.129/26
```

Enfin, nous pouvons vérifier l'adressage effectué avec la commande :

```console
$ ip address
```

#### 3) Affichez la table de routage des routeurs. Pourquoi les tables de routage ne sont-elles pas vides ? Quelle est la particularité des routes déjà présentes ? Que signifie « scope link » ?

Commande `route`, exemple sur **R1 :**

| Destination     | Gateway | Genmask         | Flags | Metric | Ref | Use | Iface |
| --------------- | ------- | --------------- | ----- | ------ | --- | --- | ----- |
| 211.230.193.196 | \*      | 255,255,255,252 | U     | 0      | 0   | 0   | eth0  |
| 211.230.193.196 | \*      | 255.255.255.252 | U     | 0      | 0   | 0   | eth1  |
| 211.230,193.192 | \*      | 255,255.255.252 | U     | 0      | 0   | 0   | eth0  |

La table de routage n’est pas vide car nous venons de configurer les interfaces (adressage IPv4).

On dit q'une route a un _scope link_ lorsqu'elle mène à une adresse de destination sur le réseau local.

#### 4) Configurez les tables de routage de manière à ce que les 3 routeurs puissent envoyer des données (ping) vers les 4 réseaux a, b, A et B.

Commande à utiliser pour configure une table de routage :

```console
$ ip route add <dest> dev <interface> via <passerelle>
```

TODO : adressage different à celui vu en TD

-   **R1** :


-   **R2** :

| Destination    | mask | Gateway        | Iface |
| -------------- | ---- | -------------- | ----- |
| 211.230.193.0  | /26  | \*             | eth0  |
| 211.230.193.64 | /26  | \*             | eth1  |
| 0.0.0.0        | /0   | 211.230.193.66 | eth1  |

-   **R3** :

| Destination     | mask | Gateway         | Iface |
| --------------- | ---- | --------------- | ----- |
| 211.230.193.128 | /26  | \*              | eth1  |
| 211.230.193.64  | /26  | \*              | eth0  |
| 211.230.193.0   | /26  | 211.230.193.68  | eth0  |
| 211.230.193.192 | /26  | 211.230.193.129 | eth1  |

## 2 Traceroute

#### 1) Sur R2, utilisez la commande « traceroute -I icmp -q 1 » vers le réseau B, en mettant comme paramètre l’adresse IP associée à l’interface eth1 de R3.

#### 2) Que renvoie cette commande ?

#### 3) A quelles interfaces et quels routeurs correspondent ces adresses ?

#### 4) Quel est le TTL du premier paquet IP envoyé par R2 ?

#### 5) Que transporte ce paquet ?

#### 6) Ce paquet parvient-il jusqu’à sa destination ? Pourquoi ?

#### 7) Qui répond à ce paquet ? Par quel type de message (protocole, type, code) ? Quelle est la signification de la réponse ?

#### 8) Quel est le TTL du 2ème paquet IP envoyé par R2 ?

#### 9) Ce paquet parvient-il jusqu’à sa destination ? Pourquoi ?

#### 10) Qui répond à ce paquet ? Par quel type de message (protocole, type, code) ? Quelle est la signification de la réponse ?

#### 11) Dans ces échanges, quels sont les messages qui permettent à traceroute de connaître l’adresse IP des routeurs qui sont sur le chemin de la destination ?

#### 12) Pourquoi l’adresse IP associée à l’interface eth0 de R3 n’est-elle pas renvoyée par traceroute ?
