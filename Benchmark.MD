# Benchmark Results

a)
Asteroid code should be contained within its own source file

UpdateExtra() call generates read access violations should be removed and replaced with a virtual update

calls to m_alive yield nothing

b)
No screen wrap

cannot rotate and shoot at the same time - likely caused by the update function interupts the player update when a bullet is fired

shooting provides a forward speed boost

No death state - not implemented	

