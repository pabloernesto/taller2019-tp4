--map = {}
position = {}
--speed (creo que deberia saberla) (Para calcular mejor)
--direction (?) Para decidir mejor...
--

function decide():
  point_index = nil
  for i,v in ipairs(map) do
    if (map[i][0] == position[0]) and (map[i][1] == position[1]) then
      point_index = i
      break
    end
  end
  -- we decide...
  return 0
end

