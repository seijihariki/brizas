
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

local function newObjectMouse (x, y, vx, vy)
  local new_object = {}
  new_object.x = x
  new_object.y = y
  new_object.r = love.math.random()*255
  new_object.g = love.math.random()*255
  new_object.b = love.math.random()*255

  new_object.dir_x = vx
  new_object.dir_y = vy
  return new_object
end


--- Move the given object as if 'dt' seconds had passed. Basically follow
--  the uniform movement equation: S = S0 + v*dt.
local function moveObject (object, dt)
  object.x = object.x + 64*object.dir_x*dt
  object.y = object.y + 64*object.dir_y*dt
  if object.x < 0 or object.x > W then
      object.dir_x = -object.dir_x
      local tmp1 = bounce_sfx:clone()
      love.audio.play(tmp1)
  end

  if object.y < 0 or object.y > H then
      object.dir_y = -object.dir_y
      local tmp2 = bounce_sfx:clone()
      love.audio.play(tmp2)
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
  MAX_OBJECTS = 2

  bounce_sfx = love.audio.newSource("bounce.ogg", "static")

  objects = {}
  for i=1,MAX_OBJECTS do
    table.insert(objects, newObject())
  end
end

--- Update the game's state, which in this case means properly moving each
--  game object according to its moving direction and current position.
function love.update (dt)
  local alpha = -.02
  local alpha_mouse = .002
  for i,object in ipairs(objects) do
    if love.mouse.isDown(1) then
      mouse_x, mouse_y = love.mouse.getPosition()
      object.dir_x = object.dir_x + (mouse_x - object.x) * alpha_mouse
      object.dir_y = object.dir_y + (mouse_y - object.y) * alpha_mouse
    end
    for j,object2 in ipairs(objects) do
      if (i < j) then
        dist_sqr = (object.y - object2.y)^2+(object.x - object2.x)^2
        if (dist_sqr <= 32*32) then
          object.dir_x = object.dir_x + (object2.x - object.x) * alpha
          object.dir_y = object.dir_y + (object2.y - object.y) * alpha
          object2.dir_x = object2.dir_x + (object.x - object2.x) * alpha
          object2.dir_y = object2.dir_y + (object.y - object2.y) * alpha
          local tmp = bounce_sfx:clone()
          love.audio.play(tmp)
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

new_obj = nil

function love.mousepressed (x, y, button)
    if button == 2 then
        new_obj = newObjectMouse(x, y, 0, 0)
    end
end

function love.mousereleased (x, y, button)
    beta = .1
    if button == 2 then
        new_obj.dir_x = (x - new_obj.x)*beta
        new_obj.dir_y = (y - new_obj.y)*beta
        table.insert(objects, new_obj)
        new_obj = nil
    end
end

--- Draw all game objects as simle white circles. We will improve on that.
--  See https://love2d.org/wiki/love.graphics.circle
function love.draw ()
  if not (new_obj == nil) then
    love.graphics.setColor(new_obj.r, new_obj.g, new_obj.b)
    love.graphics.circle('fill', new_obj.x, new_obj.y, 16, 16)
    love.graphics.line(new_obj.x, new_obj.y, love.mouse.getX(), love.mouse.getY())
  end
  for i,object in ipairs(objects) do
    love.graphics.setColor(object.r, object.g, object.b)
    love.graphics.circle('fill', object.x, object.y, 16, 16)
  end
end

