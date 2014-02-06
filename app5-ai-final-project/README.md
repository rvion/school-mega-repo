Ce compte rendu est au format markdown;
Vous pouvez le consulter directement à l'addresse 
  https://github.com/rvion/ai_projet_1
Le compte rendu apparaît en fin de page.

# Contraintes et résolution - algorithme A*

Projet par 
 * Vianney Prin
 * Rémi Vion
 
## Introduction

L'objectif de ce projet est d'appliquer l'algorithme de recherche heuristique A\* en programmant un générateur d'itinéraires pour un camion devant livrer des colis.
Comme le langage à utiliser était libre, nous avons choisi d'utiliser Ruby.

Nous avons choisi Ruby car le code est concis, facile à lire, car il existe des interpréteurs en ligne sur internet, et il est facile d'installer un interpréteur.

## L'algorithme Astar (A\*)

L'algorithme Astar est une extension de l'algorithme de Dijkstra, mais au lieux de construire progressivement un sous-graphe qui classe les sommets en commençant par les distances
les plus courtes au sommet initial et en continuant par ordre croissant des distances minimales, l'algorithme Astar se sert d'une évaluation heuristique pour estimer le meilleur
chemin puis il construit le chemin à partir de cette évaluation.

## Notre code: 

Vous pouvez trouver notre code dans le fichier

    main.rb

Vous trouverez aussi à coté de ce fichier différents autres fichiers

    * problemeX.txt -> 11 fichiers, 10 d'exemples, et 1 fait par nous pour vérifier notre code
    * planX.txt -> 11 fichiers de solutions correspondant à la sortie du programme lancé avec le problemeX.txt en entrée.

Vous pouvez lancer le fichier en tapant dans un terminal

    ruby main.rb
  
Le programme à besoin des fichiers problemeX pour fonctionner.
si vous souhaitez lancer le programme avec d'autres fichiers,
vous n'avez qu'a modifier la fonction

```ruby
def list_of_files(to=11,from=1)
  (from..to).to_a.map{|x|"probleme#{x}.txt"}
end
```

exemple:
```ruby
def list_of_files(to=11,from=1)
  ["probleme789.txt", "probleme42.txt"]
end
```


vous verrez apparaitre:

~/pj_ai$ ruby main.rb                                                                                                                                                                                                                   
   
    "solving probleme1.txt.. ok"                                                                                                                                                                                                                                                      
    "solving probleme2.txt.. ok"                                                                                                                                                                                                                                                      
    "solving probleme3.txt.. ok"                                                                                                                                                                                                                                                      
    "solving probleme4.txt.. ok"                                                                                                                                                                                                                                                      
    "solving probleme5.txt.. ok"                                                                                                                                                                                                                                                      
    "solving probleme6.txt.. ok"                                                                                                                                                                                                                                                      
    "solving probleme7.txt.. ok"                                                                                                                                                                                                                                                      
    "solving probleme8.txt.. ok"                                                                                                                                                                                                                                                      
    "solving probleme9.txt.. ok"                                                                                                                                                                                                                                                      
    "solving probleme10.txt.. ok"                                                                                                                                                                                                                                                     
    "solving probleme11.txt.. ok"            
  
le programme assume que les fichiser
### 1: parseur

Notre choix d'utiliser le langage Ruby nous a imposé de recréer un parseur dans ce langage qui soit capable de lire les fichiers "probleme":

Nous avons commencé par définir les structures de données dont nous avions besoin:
```ruby
Emplacement = Struct.new(:id, :x, :y) # liste des villes et de leur positions géographiques
Route = Struct.new(:l1, :l2, :dist) # liste des routes entre deux nodes l1 et l2 et distance
Camion = Struct.new(:id, :emplacement_id) # liste des camions et de leur position initiale
Mission = Struct.new(:id, :from, :to) # liste des missions, de leur point de départ et d'arrivée
Livraison = Struct.new(:done, :remaining, :charge)
```

puis nous avons écrit notre parseur:

```ruby
def parse_probleme_file(filename='probleme1.txt')
  data =  File.read("./#{filename}") # ouvre le fichier
  	.split('{').map{|bloc| bloc.split('}')}[1..-1].map(&:first)
    .map{|s| s.delete("\r").delete(";").split("\n").map(&:strip).select{|s| s != ''}}
    .select{|x| x != []}
  mission = {}
  @emplacements = Hash[*(data[0].map{|raw_emplacements|a=raw_emplacements.split(' '); [a[0], Emplacement.new(a[0],a[1].to_f,a[2].to_f)]}).flatten]
  colis = Hash[*data[3].map{|raw_colis| a=raw_colis.split(' ')}.flatten]
  goals = Hash[*data[4].map{|raw_goals| a=raw_goals.split(' ')}.flatten]
  colis.each{|k,v| mission[k] = Mission.new(k,v,nil)}
  goals.each{|k,v| mission[k].to = v}
  
  @routes = data[1].map{ |raw_routes| a = raw_routes.split(' '); Route.new(a[0], a[1], distance_between(@emplacements[a[0]], @emplacements[a[1]]))}
  @neighbor_nodes = Hash.new { |hash, key| hash[key] = []; }
  @dist_between = Hash.new { |hash, key| hash[key] = {}; }
  @routes.each do |r| 
    @neighbor_nodes[r.l1] << r.l2; @dist_between[r.l1][r.l2] = r.dist
    @neighbor_nodes[r.l2] << r.l1; @dist_between[r.l2][r.l1] = r.dist
  end
  return { 
    'routes' => @routes,
    'camions' => data[2].map{|raw_camions| a=raw_camions.split(' '); Camion.new(a[0], a[1])},
    'missions' => mission
  }
endend
 ```
 
Le parsing n'a pas été facilité par les différence entre la grammaire utilisé dans l'énoncé, et celles utilisés dans les exemples.
Mots en français ou anglais selon les problèmes, espaces et retour à la ligne inconstants, valeur en trop, comme les routes qui d'après
l'énoncé sont {emplacement1, emplacement2}, mais qui dans presque tous les problème présentent des champs supplémentaires.

Cette fonction retourne:
 ```ruby
{
  "routes"=>[
     #<struct Route l1="l0", l2="l1", dist=218.60160109203224, path=[]>, 
     #<struct Route l1="l0", l2="l2", dist=328.4872752482202, path=[]>, 
     #<struct Route l1="l0", l2="l4", dist=238.02287705176576, path=[]>, 
     #<struct Route l1="l0", l2="l5", dist=312.6536262383662, path=[]>, 
     #<struct Route l1="l1", l2="l2", dist=124.0348741282064, path=[]>, 
     .....
     #<struct Route l1="l6", l2="l9", dist=149.12075643584967, path=[]>, 
     #<struct Route l1="l7", l2="l9", dist=330.54197917964973, path=[]>, 
     #<struct Route l1="l8", l2="l9", dist=158.00117088173747, path=[]>
  ], 
  "camions"=>[
     #<struct Camion id="r0", emplacement_id="l3">
  ], 
  "missions" => {
     "b0" => #<struct Mission id="b0", from="l4", to="l7">, 
     "b1"=> #<struct Mission id="b1", from="l5", to="l6">
  }
}
 ```
 
Et définie aussi des variables globales.
 
les distances présente dans le tableau associatif ci-dessus sont calculées avec la fonctoin
```ruby
def distance_between(empl1, empl2)
  Math.sqrt((empl1.x-empl2.x)**2 + (empl1.y-empl2.y)**2)
end
```

## l'algorithme A*

```ruby
def find_path_with_astar(start, goal, routes)
  closedset = [] # L'ensemble des villes par lesquelles on a déjà essayé de passer. [par  Default/  l'ensemble vide []]
  openset = [start] # L'ensemble de toute les villes par lesquelles on va essayer de passer à la prochaine itérations, au départ, ne contenant que la ville de départ. [Default: set containing start]
  came_from = {}
  g_score={start => 0}
  f_score={start => g_score[start] + heuristic_cost_estimate(start, goal)} # Temps estimé jusqu'à l'arrivé.
  
  until openset.empty?
    current = openset.min_by {|node| f_score[node]}
    return [display_path(came_from, goal),g_score[goal]] if current == goal
    openset.delete(current)
    closedset << current
    @neighbor_nodes[current].each do |neighbor|
      tentative_g_score = g_score[current] + @dist_between[current][neighbor]
      tentative_f_score = tentative_g_score + heuristic_cost_estimate(neighbor, goal)
      if !(closedset.include?(neighbor) && tentative_f_score >= f_score[neighbor])
        if !openset.include?(neighbor) || tentative_f_score < f_score[neighbor]
          came_from[neighbor] = current
          g_score[neighbor] = tentative_g_score
          f_score[neighbor] = tentative_f_score
          if !openset.include?(neighbor)
            openset << neighbor
          end
        end
      end
    end
  end
  return 'failure'
end
```

l'algoritme est assez clair à lire.

la fonction heuristique est celle-ci:

```ruby
def heuristic_cost_estimate(start, goal)
  return distance_between(@emplacements[start],@emplacements[goal])
end
```

pour transformer l'algorithme astar en dijkstra, il suffit d'avoir une heuristique qui retourne 0:

```ruby
def heuristic_cost_estimate(start, goal)
  return 0
end
```

La dernière partie à expliquer de notre code est celle qui liste tous les ordres de livraisons possibles, 
le reste n'étant que l'évaluation des diffiérents parcours possible, la selection du plus court, et
l'affichage du résultat dans un fichier texte.


énumération des chemins possible:
```ruby
def enumerate_possible_livraisons_order(livraisons, nb_livraisons=nil)
  if nb_livraisons.nil? # si c'est le tout premier appel de cette fonction récursive
  	nb_livraisons = livraisons.values.length * 2
    return enumerate_possible_livraisons_order([Livraison.new([], livraisons, 0, [])], nb_livraisons)
  elsif livraisons.first.done.length == nb_livraisons # si on a énuméré toutes les solutions possibles
    return livraisons
  else # sinon
    new_livraisons = []
    livraisons.each do |livraison|
      a = livraison.done.dup
      livraison.remaining.each do |k,v|
        l = livraison.dup
        l.done = livraison.done.dup
        l.remaining = livraison.remaining.dup
        l.msg = livraison.msg.dup
      	next_dest = l.remaining[k].from
      	if next_dest == nil
      	  next_dest = l.remaining[k].to
          l.msg << "unloadColis(#{l.remaining[k].id})"
          l.remaining.delete k
          l.charge -= 1
      	else
          if l.charge < 2
            l.remaining[k] = livraison.remaining[k].dup
            l.msg << "loadColis(#{l.remaining[k].id})"
            l.remaining[k].from = nil
            l.charge += 1
          else
            next_dest = nil
          end
      	end
        if next_dest
      	  l.done << next_dest
      	  new_livraisons << l
        end
      end
    end
  	return enumerate_possible_livraisons_order(new_livraisons, nb_livraisons)
  end
end
```

cette fonction retourne:

```ruby
[#<struct Livraison done=["l0", "l1", "l2", "l3"], msg=["loadColis(b0)", "unloadColis(b0)", "loadColis(b1)", "unloadColis(b1)"]>, 
 #<struct Livraison done=["l0", "l2", "l1", "l3"], msg=["loadColis(b0)", "loadColis(b1)", "unloadColis(b0)", "unloadColis(b1)"]>, 
 #<struct Livraison done=["l0", "l2", "l3", "l1"], msg=["loadColis(b0)", "loadColis(b1)", "unloadColis(b1)", "unloadColis(b0)"]>, 
 #<struct Livraison done=["l2", "l0", "l1", "l3"], msg=["loadColis(b1)", "loadColis(b0)", "unloadColis(b0)", "unloadColis(b1)"]>, 
 #<struct Livraison done=["l2", "l0", "l3", "l1"], msg=["loadColis(b1)", "loadColis(b0)", "unloadColis(b1)", "unloadColis(b0)"]>, 
 #<struct Livraison done=["l2", "l3", "l0", "l1"], msg=["loadColis(b1)", "unloadColis(b1)", "loadColis(b0)", "unloadColis(b0)"]>]
```

Il ne reste plus, comme dit précédemment, qu'à évaluer ces ordres de livraisons, trouver le plus court en km, et l'afficher présenté comme demandé dans l'énoncé.

## rapidité d'exécution:

 * Les résultats de l'algorithme astar sont mis en cache pour que tout soit rapide.
 * L'évaluation des 10 problèmes (plus du notre) prend 0.1 sec sur notre machine virtuelle utilisée pour développer tout ça en ligne sur https://www.nitrous.io

## overture sur d'éventuelles améliorations possible non spécifiées

pour gagner en vitesse, on peut utiliser des structures de données appellées Heap au lieu de liste pour stoquer les noeuds et leur f_score et g_score.