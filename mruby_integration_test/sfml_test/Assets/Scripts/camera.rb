class Camera
  
  def onCreate
    @position = Vec3.new(0, 0, 4)
  end
  
  def update(elapsed)
    move_offset = elapsed * moveSpeed
    
    @scene.camera.move(move_offset * @scene.camera.forward) if Input.Should :strafe_forward
    @scene.camera.move(move_offset * -@scene.camera.forward) if Input.Should :strafe_backward
    
    @scene.camera.move(move_offset * @scene.camera.right) if Input.Should :strafe_right
    @scene.camera.move(move_offset * -@scene.camera.right) if Input.Should :strafe_left
  end
  
end