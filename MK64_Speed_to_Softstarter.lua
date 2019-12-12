function round(num) -- arredondamento
  return math.floor(num + 0.5)
end

while true do
    kart = {} --kart data 
    kart.seno = 0xF6B04
    kart.cosseno = 0xF6B0C
    kart.x_pos_address = 0x0F69A4
    kart.xspeed_pos_address = 0x0F69C4 
    kart.y_pos_address = 0xF69A8
    kart.z_pos_address = 0x0F69AC
    kart.zspeed_pos_address = 0x0F69CC

  kart_x      = mainmemory.readfloat(kart.x_pos_address,  true)
  kart_xv     = mainmemory.readfloat(kart.xspeed_pos_address, true) * 12
  kart_z      = mainmemory.readfloat(kart.z_pos_address,  true)
  kart_zv     = mainmemory.readfloat(kart.zspeed_pos_address, true) * 12
  kart_speed  = math.sqrt(kart_xv^2+kart_zv^2) -- the sum of the square of x speed and z speed, so we have both speeds being analysed, Y speed doesnt matter since the kart is stopped when Y speed changes
  realthing = round(kart_speed)

 local file = assert(io.open("teste.txt", "w"))
 if round(kart_speed) <= 9 then file:write("0"..round(kart_speed))
 else 
 file:write(round(kart_speed))
 end
 file:close()
	emu.frameadvance();
end