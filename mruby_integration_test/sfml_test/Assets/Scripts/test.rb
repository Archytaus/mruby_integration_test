class Test
  DEGREES_PER_SECOND = 90

  def onCreate
    puts "My ID: #{@id.to_s}"
    puts "Instance variables: #{self.instance_variables}"
  end

  def update(elapsed)

    test = Vec3.new(0, 1, 0) + Vec3.new(1, 0, 0) + Vec3.new(0, 0, 1)
    test2 = test * Vec3.new(3, 3, 3)
    test3 = test2 * 2
    test4 = Vec3.new(2) * test3
    # test2 = test - Vec3.new(6, 6, 6)

    @transform.rotation.y += elapsed * DEGREES_PER_SECOND
    @transform.rotation.y -= 360 while @transform.rotation.y > 360

  end
end