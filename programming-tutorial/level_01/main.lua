
-- At first, we'll try to keep everything commented, but that will be dropped
-- soon enough, so get used to figuring things out!

-- "local" variables mean that they belong only to this code module. More on
-- that later.

-- Window resolution
local W, H

-- Maximum number of obejcts
local MAX_OBJECTS

-- The list of all game objects
local objects

-- Holds the source object containing the "bounce" sound effect
local bounce_sfx

--[[ Auxiliary functions ]]--

--- Creates a new game object.
--  We start with an empty table, then define the 'x' and 'y' fields as the
--  coordinates of the object, and in the end choose a move direction, in
--  radians, that is converted to a unitary directional vector using a little
--  trigonometry.
--  See https://love2d.org/wiki/love.math.random
local function newObject ()
  local new_object = {}
  new_object.x = love.math.random()*W
  new_object.y = love.math.random()*H
  new_object.r = love.math.random()*255
  new_object.g = love.math.random()*255
  new_object.b = love.math.random()*255

  local dir = love.math.random()*2*math.pi
  new_object.dir_x = math.cos(dir)
  new_object.dir_y = math.sin(dir)
  return new_object
end

--- Move the given object as if 'dt' seconds had passed. Basically follow
--  the uniform movement equation: S = S0 + v*dt.
local function moveObject (object, dt)
  object.x = object.x + 64*object.dir_x*dt
  object.y = object.y + 64*object.dir_y*dt
  if object.x < 0 or object.x > W then
      object.dir_x = -object.dir_x
      love.audio.play(bounce_sfx)
  end

  if object.y < 0 or object.y > H then
      object.dir_y = -object.dir_y
      love.audio.play(bounce_sfx)
  end
end

--[[ Main game functions ]]--

--- Here we load up all necessary resources and information needed for the game
--  to run. We start by getting the screen resolution (which will be used for
--  drawing) then define the maximum number of objects. Finally we create a
--  list of game objects to draw and interact. Note that we also use a table
--  for the list, but in a different way than above.
--  See https://love2d.org/wiki/love.graphics.getDimensions
function love.load ()
  W, H = love.graphics.getDimensions()
  MAX_OBJECTS = 32

  bounce_sfx = love.audio.newSource("bounce.ogg", "static")

  objects = {}
  for i=1,MAX_OBJECTS do
    table.insert(objects, newObject())
  end
end

--- Update the game's state, which in this case means properly moving each
--  game object according to its moving direction and current position.
function love.update (dt)
  local alpha = 1

  for i,object in ipairs(objects) do
    for j,object2 in ipairs(objects) do
      if (i < j) then
        dist_sqr = (object.y - object2.y)^2+(object.x - object2.x)^2
        if (dist_sqr <= 32*32) then
          object.dir_x = 0*object.dir_x + (object2.x - object.x) * alpha
          object.dir_y = 0*object.dir_y + (object2.y - object.y) * alpha
          object2.dir_x = 0*object2.dir_x + (object.x - object2.x) * alpha
          object2.dir_y = 0*object2.dir_y + (object.y - object2.y) * alpha
        end
      end
    end
  end
  for i,object in ipairs(objects) do
    moveObject(object, dt)
  end
end

--- Detects when the player presses a keyboard button. Closes the game if it
--  was the ESC button.
--  See https://love2d.org/wiki/love.event.push
function love.keypressed (key)
  if key == 'escape' then
    love.event.push 'quit'
  end
end

--- Draw all game objects as simle white circles. We will improve on that.
--  See https://love2d.org/wiki/love.graphics.circle
function love.draw ()
  for i,object in ipairs(objects) do
    love.graphics.setColor(object.r, object.g, object.b)
    love.graphics.circle('fill', object.x, object.y, 16, 16)
  end
end

