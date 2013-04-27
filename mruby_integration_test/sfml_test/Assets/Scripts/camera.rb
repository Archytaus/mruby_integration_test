class MyCamera
  MOVE_SPEED = 10

  def onCreate
    puts "Instance variables: #{self.instance_variables}"
    puts "Inspect: #{self.inspect}"
    puts "Inspect: #{self.public_methods}"
    # @camera.position = Vec3.new(0, 0, 4)
  end

  def update(elapsed)
    move_offset = elapsed * MOVE_SPEED

    @camera.move(Vec3.new(move_offset) * @camera.forward) if Input.pressed? :w
    @camera.move(Vec3.new(move_offset) * -@camera.forward) if Input.pressed? :s

    @camera.move(Vec3.new(move_offset) * @camera.right) if Input.pressed? :d
    @camera.move(Vec3.new(move_offset) * -@camera.right) if Input.pressed? :a
  end
end