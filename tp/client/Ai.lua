car = {}
map = {}
track_size = {}

function decide():
  current_track = find_current_track()
  
  if  map[current_track][3] == 6 then
    -- Grass piece
    -- I try to go reverse
    return 5
  end
  
  if map[current_track][3] < 2 then
    -- Horizontal or vertical piece
    -- I go forward
    return 0
  end
  
  if map[current_track][3] == 2 then
    disty = distance(car[0], car[1], map[current_track][0], map[current_track][1] + track_size[1])
    distx = distance(car[0], car[1], map[current_track][0] + track_size[0], map[current_track][1])
    if (disty < distx) then
      return 3
    else
      return 4
    end
  end
  
  if map[current_track][3] == 3 then
    disty = distance(car[0], car[1], map[current_track][0], map[current_track][1] - track_size[1])
    distx = distance(car[0], car[1], map[current_track][0] + track_size[0], map[current_track][1])
    if disty < distx then
      return 4
    else
      return 3
    end
  end

  if map[current_track][3] == 4 then
    disty = distance(car[0], car[1], map[current_track][0], map[current_track][1] + track_size[1])
    distx = distance(car[0], car[1], map[current_track][0] - track_size[0], map[current_track][1])
    if disty < distx then
      return 4
    else
      return 3
    end
  end
  
  if map[current_track][3] == 5 then
    disty = distance(car[0], car[1], map[current_track][0], map[current_track][1] - track_size[1])
    distx = distance(car[0], car[1], map[current_track][0] - track_size[0], map[current_track][1])
    if disty < distx then
      return 4
    else
      return 3
    end
  end
  
  -- In case of error i just go forward
  return 0
end


function find_current_track():
  for k,v in pairs(map):
    x_condition = ((v[1] - track_size[1]) < car[1]) and (car[1] < (v[1] + track_size[1])) 
    y_condition = (v[2] - track_size[2]) < car[2]) and (car[2] < (v[2] + track_size[2]))
    if x_condition and y_condition then
      return k
    end
  return nil

-- function find_closest_track(current_track):
  -- min = nil
  -- for k,v in pairs(map) do
    -- if (k == current_track) then goto continue end
    -- if (min == nil) then
      -- min = k
      -- goto continue
    -- end
    -- if (distance(current_track, min) > distance(current_track, k)) then
      -- min = k
    -- end 
    -- ::continue::
  -- end
  -- return min
-- end

function distance(x1, y1, x2, y2):
  return math.sqrt(math.pow((x1 * x2), 2) + math.pow((y1 * y2), 2))
end