class MyCamera
  MOVE_SPEED = 10
  MOUSE_SENSITIVITY = 0.1

  def onCreate
    # @camera.position = Vec3.new(0, 0, 4)
  end

  def update(elapsed)
    move_offset = elapsed * MOVE_SPEED

    @camera.move(Vec3.new(move_offset) * @camera.forward) if Input.pressed? :w
    @camera.move(Vec3.new(move_offset) * -@camera.forward) if Input.pressed? :s

    @camera.move(Vec3.new(move_offset) * @camera.right) if Input.pressed? :d
    @camera.move(Vec3.new(move_offset) * -@camera.right) if Input.pressed? :a

    @camera.rotate(Input.mouse_pos * Vec2.new(MOUSE_SENSITIVITY))
  end
end