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
  current_track = find_current_track
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
  for k,v in pairs(map):
    -- 
  return min
end