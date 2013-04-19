class Test
  DEGREES_PER_SECOND = 180
  
  def onCreate
    puts "My ID: #{@id.to_s}"
    puts "Instance variables: #{self.instance_variables}"
  end
  
  def onDestroy
  end
  
  def update(elapsed)
    @rotation.y += elapsed * DEGREES_PER_SECOND
    @rotation.y -= 360 while @rotation.y > 360
  end
end