class Test
  DEGREES_PER_SECOND = 90

  def onCreate
    puts "My ID: #{@id.to_s}"
    puts "Instance variables: #{self.instance_variables}"
  end

  def update(elapsed)

    @transform.rotation.y += elapsed * DEGREES_PER_SECOND
    @transform.rotation.y -= 360 while @transform.rotation.y > 360

  end
end