car = {}
map = {}
track_size = {}
prev_track = {}
function decide():
  --Random number implementation
  math.randomseed(os.time())
  r = math.random(0,6);
  return r

  -- Real implementation
  --First iteration
  if next(prev_track) == nil then
    return 0
  end
  -- Any other iteration
  current_track = find_current_track
  closest_track = find_closest_track
  -- Now what?
end


function find_current_track():
  for k,v in pairs(map):
    x_condition = ((v[1] - track_size[1]) < car[1]) and (car[1] < (v[1] + track_size[1])) 
    y_condition = (v[2] - track_size[2]) < car[2]) and (car[2] < (v[2] + track_size[2]))
    if x_condition and y_condition then
      return k
    end
  return nil

function find_closest_track(current_track):
  min = nil
  for k,v in pairs(map) do
    if (k == current_track) then goto continue end
    if (min == nil) then
      min = k
      goto continue
    end
    if (distance(current_track, min) > distance(current_track, k)) then
      min = k
    end 
    ::continue::
  end
  return min
end

function distance(k1, k2):
  return math.sqrt(math.pow((map[k1][1] * map[k2][1]), 2) + math.pow((map[k1][2] * map[k2][2]), 2))
end