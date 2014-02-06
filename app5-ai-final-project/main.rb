Emplacement = Struct.new(:id, :x, :y) # liste des villes et de leur positions géographiques
Route = Struct.new(:l1, :l2, :dist) # liste des routes entre deux nodes l1 et l2 et distance
Camion = Struct.new(:id, :emplacement_id) # liste des camions et de leur position initiale
Mission = Struct.new(:id, :from, :to) # liste des missions, de leur point de départ et d'arrivée

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
end

def distance_between(empl1, empl2)
  Math.sqrt((empl1.x-empl2.x)**2 + (empl1.y-empl2.y)**2)
end

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

def heuristic_cost_estimate(start, goal)
  return distance_between(@emplacements[start],@emplacements[goal])
  # return 0
end

def display_path(came_from, current_node)
  return ([display_path(came_from, came_from[current_node]), current_node]).flatten if came_from[current_node]
  return current_node
end

Livraison = Struct.new(:done, :remaining, :charge, :msg)

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

def list_of_files(to=11,from=1)
  (from..to).to_a.map{|x|"probleme#{x}.txt"}
end

def solve_probleme(input_filename='probleme1.txt')
  d = parse_probleme_file(input_filename)
  start = d['camions'][0].emplacement_id
  macro_routes = {}
  min_score = nil
  best_livraison = nil
  
  enumerate_possible_livraisons_order(d['missions']).each do |livraison_test|
    livraison_order = livraison_test.done
    prev = start
    score = 0
    livraison_order.each do |dest|
      seg12 = "#{prev}-#{dest}"
      seg21 = "#{dest}-#{prev}"
      macro_routes[seg12] = macro_routes[seg21] = find_path_with_astar(prev, dest, d['routes']) if !macro_routes[seg12]
      score += macro_routes[seg12][1]
      prev = dest
    end
    if !min_score || score < min_score
      best_livraison = livraison_test
      min_score = score
    end
  end
  idx = 0
  output_filename = "./plan#{input_filename.split('.').first[8..-1]}.txt"
  File.open(output_filename, 'w') do |f| 
    f.write("Plan { // #{min_score} km long\n")
    f.write("  a#{idx}: startAt(#{start})\n"); idx+=1
    [start,best_livraison.done].flatten.each_with_index do |bl,i| 
      macro_routes["#{bl}-#{best_livraison.done[i]}"].first[1..-1].each_with_index do |node, index|
        f.write("  a#{idx}: goTo(#{node})\n"); idx+=1
      end rescue nil      
    if best_livraison.done[i]
        f.write("  a#{idx}: #{best_livraison.msg.shift}\n"); idx+=1 
      end
    end
    f.write("\n")
    (0..idx-1).each{ |a| f.write("  a#{a} < a#{a+1}\n")}
    f.write("}\n")
  end
  'ok' 
end

list_of_files.each do |file_name|
  p "solving #{file_name}.. #{solve_probleme(file_name)}"
end