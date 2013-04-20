class Camera
  MOVE_SPEED = 2
  
  def onCreate
    Scene.camera.position = Vec3.new(0, 0, 4)
  end
  
  def update(elapsed)
    move_offset = elapsed * MOVE_SPEED
    
    Scene.camera.move(move_offset * @scene.camera.forward) if Input.pressed :strafe_forward
    Scene.camera.move(move_offset * -@scene.camera.forward) if Input.pressed :strafe_backward
    
    Scene.camera.move(move_offset * @scene.camera.right) if Input.pressed :strafe_right
    Scene.camera.move(move_offset * -@scene.camera.right) if Input.pressed :strafe_left
  end
end