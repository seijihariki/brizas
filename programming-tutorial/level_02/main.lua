
-- GAME CONSTANTS

local WIDTH, HEIGHT = 20, 15

local TILE_SIZE = 32

local TILES = {}

local STATES = {
  PICK_UNIT = 1,
  MOVE_UNIT = 2,
  ATTACK_TARGET = 3
}

local DIRS = {
  right = {0, 1},
  left = {0, -1},
  up = {-1, 0},
  down = {1, 0},
}

local MAP_BASE = {
  -- Each cell has the tile type id, which are indexes on the TILES table
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 2, 2, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
}

local PLAYER_UNIT_POSITIONS = {
  -- Format: {row, column}
  {3, 7},
  {11, 8},
  {5, 14}
}

local CPU_UNIT_POSITIONS = {
  -- Format: {row, column}
  {9, 11},
  {12, 3},
  {2, 17}
}

-- GLOBAL VARIABLES

-- The battlefield map
local map
-- Array of player units
local player_units
-- Array of CPU units
local cpu_units
-- Current state of the game
local state
-- Control cursor
local cursor
-- Currently selected unit
local selected_unit

-- HELPER FUNCTIONS

-- GAME LOGIC

local function makeUnit (side, pos, id)
  return {
    hp = 100,
    atk = 20,
    side = side,
    pos = pos,
    id = id,
    alive = true
  }
end

local function name(unit)
  return unit.side .. '-' .. unit.id
end

function love.load ()
  -- Load map
  map = {}
  for i=1,HEIGHT do
    map[i] = {}
    for j=1,WIDTH do
      map[i][j] = { bg = MAP_BASE[i][j], fg = false }
    end
  end
  -- Load units
  player_units = {}
  cpu_units = {}
  for i,pos in ipairs(PLAYER_UNIT_POSITIONS) do
    player_units[i] = makeUnit('player', pos, i)
    map[pos[1]][pos[2]].fg = player_units[i]
  end
  for i,pos in ipairs(CPU_UNIT_POSITIONS) do
    cpu_units[i] = makeUnit('cpu', pos, i)
    map[pos[1]][pos[2]].fg = cpu_units[i]
  end
  -- Set game state
  state = STATES.PICK_UNIT
  cursor = {10, 8}
  selected_unit = 0
  -- load awesome graphics
  terrainsheet = love.graphics.newImage("assets/imgs/minecraft.jpg")
  ninja = love.graphics.newImage("assets/imgs/ninja.png")

  -- graphics ninja
  ninja_tile_size = 88
  ninja_stance_normal = love.graphics.newQuad(0, 2 * ninja_tile_size, ninja_tile_size, ninja_tile_size, ninja:getDimensions())
  ninja_stance_attack = love.graphics.newQuad(ninja_tile_size, ninja_tile_size, ninja_tile_size, ninja_tile_size, ninja:getDimensions())
  -- graphics tiles
  tile_size = 80
  grass = love.graphics.newQuad(0, 0, tile_size, tile_size, terrainsheet:getDimensions())
  dirt = love.graphics.newQuad(2 * tile_size, 0, tile_size, tile_size, terrainsheet:getDimensions())
  cobble = love.graphics.newQuad(0, tile_size, tile_size, tile_size, terrainsheet:getDimensions())

  TILES[1] = grass
  TILES[2] = dirt
  TILES[3] = cobble
  -- Load sounds
  move_fx = love.audio.newSource("assets/sounds/move.mp3", "static")
  miss_fx = love.audio.newSource("assets/sounds/miss.mp3", "static")
  battle_fx = love.audio.newSource("assets/sounds/battle.mp3", "static")
  pos_battle_fx = love.audio.newSource("assets/sounds/pos_battle.mp3", "static")
  bgm = love.audio.newSource("assets/sounds/bgm.mp3", "stream")
  bgfx = love.audio.newSource("assets/sounds/bgfx.mp3", "stream")
  cursor_move_fx = love.audio.newSource("assets/sounds/cursor_move.mp3", "static")
  cursor_select_fx = love.audio.newSource("assets/sounds/cursor_select.mp3", "static")

  love.audio.play(bgm)
  love.audio.play(bgfx)
end

local function attack (attacker, defender)
  print(('Unit %s caused %d damage on unit %s'):format(name(attacker),
                                                       attacker.atk,
                                                       name(defender)))
  defender.hp = math.max(0, defender.hp - attacker.atk)
  love.audio.play(battle_fx)
  --love.audio.play(pos_battle_fx)
  if defender.hp == 0 then
    print(('Unit %s perished!'):format(name(defender)))
    defender.alive = false
    map[defender.pos[1]][defender.pos[2]].fg = false
  end
end

local function miss (attacker)
  love.audio.play(miss_fx)
  print(('Unit %s attacked the air!'):format(name(attacker)))
end

local function enemyTurn ()
  -- Do nothing if there is no unit alive
  if not (cpu_units[1].alive or cpu_units[2].alive or cpu_units[3].alive) then
    return
  end
  -- Pick a random unit
  local enemy
  repeat
    enemy = cpu_units[love.math.random(0, 3)]
  until enemy and enemy.alive
  -- Choose a random target tile to move to
  local new_pos = {}
  repeat
    new_pos[1] = love.math.random(HEIGHT)
    new_pos[2] = love.math.random(WIDTH)
  until not map[new_pos[1]][new_pos[2]].fg
  map[enemy.pos[1]][enemy.pos[2]].fg = false
  map[new_pos[1]][new_pos[2]].fg = enemy
  enemy.pos[1] = new_pos[1]
  enemy.pos[2] = new_pos[2]
  -- Try to attack all sides in sequence until a player unit is hit
  local target_pos = {}
  for name,dir in pairs(DIRS) do
    target_pos[1] = enemy.pos[1] + dir[1]
    target_pos[2] = enemy.pos[2] + dir[2]
    if target_pos[1] <= HEIGHT and target_pos[1] >= 1 then
      if target_pos[2] <= WIDTH and target_pos[2] >= 1 then
        local target = map[target_pos[1]][target_pos[2]].fg
        if target and target.side == 'player' then
          attack(enemy, target)
          return
        end
      end
    end
  end
  miss(enemy)
end

function love.update (dt)
  if bgm:isStopped() then
      love.audio.rewind(bgm)
      love.audio.play(bgm)
  end

  if bgfx:isStopped() then
      love.audio.rewind(bgfx)
      love.audio.play(bgfx)
  end
end

function love.keypressed (key)
  -- Store whether the key pressed was a directional key
  local dir = DIRS[key]
  -- Store the unit under the cursor, if any
  local target_unit = map[cursor[1]][cursor[2]].fg
  if state == STATES.PICK_UNIT then
    -- Player moved cursor
    if dir then
      cursor[1] = math.max(1, math.min(cursor[1] + dir[1], HEIGHT))
      cursor[2] = math.max(1, math.min(cursor[2] + dir[2], WIDTH))
      local new_beep_source = cursor_move_fx:clone()
      love.audio.play(new_beep_source)
      -- Player picked a unit
    elseif key == 'return' and target_unit then
      if target_unit.side == 'player' then
        selected_unit = target_unit
        print('Picked unit ' .. name(selected_unit))
        state = STATES.MOVE_UNIT
      end
    end
  elseif state == STATES.MOVE_UNIT then
    -- Player moved cursor
    if dir then
      cursor[1] = math.max(1, math.min(cursor[1] + dir[1], HEIGHT))
      cursor[2] = math.max(1, math.min(cursor[2] + dir[2], WIDTH))
      local new_beep_source = cursor_move_fx:clone()
      love.audio.play(new_beep_source)
    -- Player selected a tile to move to
    elseif key == 'return' then
      love.audio.play(cursor_select_fx)
      -- Target tile has a unit on it
      if target_unit then
        error('Oh-oh, try another tile...')
      -- Move unit
      else
        map[selected_unit.pos[1]][selected_unit.pos[2]].fg = false
        map[cursor[1]][cursor[2]].fg = selected_unit
        selected_unit.pos[1] = cursor[1]
        selected_unit.pos[2] = cursor[2]
        love.audio.play(move_fx)
        state = STATES.ATTACK_TARGET
      end
    end
  elseif state == STATES.ATTACK_TARGET then
    -- Player changed attack direction
    if dir then
      cursor[1] = math.max(1, math.min(selected_unit.pos[1] + dir[1], HEIGHT))
      cursor[2] = math.max(1, math.min(selected_unit.pos[2] + dir[2], WIDTH))
      local new_beep_source = cursor_move_fx:clone()
      love.audio.play(new_beep_source)
    -- Attack target chosen
    elseif key == 'return' then
      if target_unit then
        if target_unit.side == 'cpu' then
          attack(selected_unit, target_unit)
        else
          print("You can't attack your own unit!")
          return
        end
      else
        miss(selected_unit)
      end
      state = STATES.PICK_UNIT
      enemyTurn()
    end
  end
end

-- GAME RENDERING

function love.draw ()
  local g = love.graphics
  -- Draw map
  for i=1,HEIGHT do
    for j=1,WIDTH do
      local target = map[i][j].fg
      g.push()
      g.translate((j - 1)*TILE_SIZE, (i - 1)*TILE_SIZE)
      g.setColor(255, 255, 255)
      curr_quad = TILES[map[i][j].bg]
      g.draw(terrainsheet, curr_quad, 0, 0, 0, TILE_SIZE/tile_size)
      -- Draw units
      if target then
        if target.side == 'player' then
          g.setColor(0, 0, 255)
        else
          g.setColor(255, 0, 0)
        end
        g.draw(ninja, ninja_stance_normal, 0, 0, 0, TILE_SIZE/ninja_tile_size)
        -- g.polygon('fill', TILE_SIZE/2, 0, TILE_SIZE, TILE_SIZE, 0, TILE_SIZE)
        g.print(target.id, 0, 0)
      end
      g.pop()
    end
  end
  -- Highlight currently selected unit
  if state == STATES.MOVE_UNIT then
    g.push()
    local pos = selected_unit.pos
    g.translate(TILE_SIZE*(pos[2] - 1), TILE_SIZE*(pos[1] - 1))
    g.setColor(0, 255, 0, 255)
    g.rectangle('line', 0, 0, TILE_SIZE, TILE_SIZE)
    g.pop()

    for i=1,HEIGHT do
      for j=1,WIDTH do
        g.push()
        g.translate((j - 1)*TILE_SIZE, (i - 1)*TILE_SIZE)
        g.setColor(0, 255, 0, 255)
        if (false) then
        end
        g.pop()
      end
    end
  end
  -- Highlight available attack targets
  if state == STATES.ATTACK_TARGET then
    g.push()
    local pos = selected_unit.pos
    g.translate(TILE_SIZE*(pos[2] - 1), TILE_SIZE*(pos[1] - 1))
    g.setColor(0, 255, 0, 255)
    for name,dir in pairs(DIRS) do
      g.rectangle('line', TILE_SIZE*dir[2], TILE_SIZE*dir[1], TILE_SIZE,
                  TILE_SIZE)
    end
    g.pop()
  end
  -- Draw cursor
  if cursor then
    g.push()
    g.translate(TILE_SIZE*(cursor[2] - 1), TILE_SIZE*(cursor[1] - 1))
    g.setColor(255, 255, 255, 255)
    g.rectangle('line', -1, -1, TILE_SIZE+2, TILE_SIZE+2)
    g.pop()
  end
end
