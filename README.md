# Teiwaz
Game engine made to make Bubble bobble, but it should also be able to run games simular to this
 









# Design choices

## Singletons
I am not really a fan of singletons, I have the feeling that  I don't have a lot of control over it. 
I try yo avoid them everywhere I can but for contentmanger I make an exception.
I use something like gamecontext which is made before the engine runs, and I give it to the scene
the scene, gameobject and Component are able to access this pointer.
This is a singleton but not a static variable. which gives me more control (or at least I think so)

## string over wstring
because the scene is saved in binary format, writing both string and wstring is hard.
if wfstream is used instead of normal stream you alsways save 2(wchar_t) bytes instead of 1.
This gave a lot of porblems when writing int (some ints do not work) and you are also unable to save a byte.
for these 2 reason I made sure that every string saved in a component is a normal one so it can be read easly.
