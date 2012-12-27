MathIO.hpp : fonctions de créations de matrice à partir d'un fichier.

ttt.cpp : fonctions de manipulation de matrice, appendMatrix;
draw.cpp : fonction de dessin, d'affichage.

Tensor3d : la classe de notre tensor;

input/ image1,2,3 sont les images chargées. list1.list and co sont les listes de point chargés dans le main. Ne pas les modifier.

input/list-user/  list1.list and co sont des listes avec un point bidon - nécessaire pour que les fonctions de MathIO ne freeze pas l'écran - dans l'optique de sauvegarder les point de l'utilisateur.

save/ des "impressions" de nos matrices et vecteurs, pour vérifications; A la matrice A 28*27, A2 la matrice du transfert 4*2, U et V -svd2 les matrices de la svd du transfert.
savelist1 et 2, enregistrent les points cliqués pour le transfert;

t est le vecteur représentant les valeurs du tenseur.

X2 notre vecteur solution tant attendu


Après divers chargements et initialisation :

------- test zone ---------  ~ line 115 

Création d'une instance de tenseur à partir des listes de points de
Nozick, nommé Titi.
On construit immédiatement la matrice A; on SVDéise, on stocke dans un vecteur t comme l'énoncé le dit les valeurs du tenseur, qui sont les solutions "at least square" de la At = 0, qui sont dans la dernière colonne de V -cf cours- qui pour le coups a été automatiquement transposée, pas besoin de s'en occuper.

avec setVal, on insère dans les matrices L,M et N de l'objet Titi, qui représente le tenseur, les valeurs de t;
C'est particulièrement moche; le code est je l'avous compliqué, surtout setVal, mais ça remplis bien tant mieux;

printTensor affiche dans le terminal notre tensor, mais bon osef;
On prépare un vecteur X2


Boucle de rendu, on dessine les listes de points fournis par Nozick ... ou pas, car je donne un rayon de 0 aux fonctions fill_circle (avant dernier paramètre) pour ne pas polluer l'écran.

Les nouveaux points sont affichés néanmoins au clic ; Concernant le transfert, il vaut mieux en attendant que ça fonctionne utiliser set_pixel ou draw_grid comme j'ai fait car fill_circle ne gère pas les points en bordure -> core_dumped

Les événements sont pas compliqués à comprendre ; on démarre l'exécutable ; on appuie sur l pour s'autoriser à cliquer des points sur les prems images ; clic droit permet de connaitre les coords dans le terminal.

Une fois un clic à gauche et un clic à droite, calcul du transfert une seule fois (grâce à count1 et count2 ) et dessin du point.

Attention à faire cliquer un point sur img1/img2 puis sur img2/img1
, sinon seg fault.
les touches q et suppr et echap permettent de quitter le programme.



Mathématique : 
Dans buildMatrixA de Tensor3d.cpp :


On construit une matrice A 28*27, 28 équations pour 27 inconnues.
28, c'est 4*7. 27 c'est 3*9.
J'explique :
On a en fait pour imager une matrice : 
de 7 lignes, chaque lignes subdiviser en 4 lignes (selon les variations de i et l), soit 28 :

la ligne i==0 et l==0
la ligne i==0 et l==1
la ligne i==1 et l==0
la ligne i==1 et l==1

ce groupet de ligne multiplier par 7 (nos 7 points de correspondances; on pourrait rajouter r points, il faudrait rajouter à chq fois 4r lignes...


Pour les colonnes, on a 3 colonnes , k=0, k=1, k=2.
Ces 3 colonnes sont subdivisées en 9 colonnes donc 27 inconnues.
k=0, ça signifiera qu'on accède à la matrice L de Titi notre Tensor3d. k=1 c'est pour M, k=2 c'est pour N.
Et dans ces matrices 3*3, on y bourre nos 9 inconnues.

Pour chq ligne de A, il faut mettre 12 valeurs, 4 par sections de k.

Elle le fait, et bien; 
4p +2i +l permet d'accèder à la bonne ligne grâce aux nbx if;
l'indice de colonne est soigneusement déterminé grâce à un brouillon sur papier ;-)

Le transfert :

En fait c'est pas exactement ce qu'à dit Nozick dans l'énoncé.
Il nous faut une matrice A2 4*2, et résoudre.
A2 * X = b ; b c'est un vecteur de 4 lignes qui contient des valeurs non nulles, ceux sont les valeurs du points cliqués, affecté de coefficient du tenseur qu'on a calculé aupparavent.

b a 4 lignes, car on a 4 équations. Ce n'est pas 2 lignes comme je l'ai pensé car on a 2 inconnues.

C'est comme ça qu'on l'écrit car la soit disante 3ème inconnue du point à calculer est égale à 1, nous sommes dans le plan.


Le résultat est mis dans le vecteur X2 de taille 2. 



Voilà le topo, maintenant la pratique : 

On prend la formule section 3.6 de la page 7 de l'énoncé



























































