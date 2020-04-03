# Teiwaz
Game engine made to make Bubble bobble, but it should also be able to run games simular to this
 









###### Design choices

#Singletons
I am not really a fan of singletons, I have the feeling that  I don't have a lot of control over it. 
I try yo avoid them everywhere I can but for contentmanger I make an exception.
I use something like gamecontext which is made before the engine runs, and I give it to the scene
the scene, gameobject and Component are able to access this pointer.
This is a singleton but not a static variable. which gives me more control (or at least I think so)