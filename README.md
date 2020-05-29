# Teiwaz
Game engine made to make Bubble bobble, but it should also be able to run games simular to this
 
Want to know what I'm working on? https://trello.com/b/G3iIxhFO/teiwaz-engine








# Design choices

## Singletons
I am not really a fan of singletons, I have the feeling that  I don't have a lot of control over it. 
I try yo avoid them everywhere I can but for contentmanger I make an exception.
I use something like gamecontext which is made before the engine runs, and I give it to the scene
the scene, gameobject and Component are able to access this pointer.
This is a singleton but not a static variable. which gives me more control (or at least I think so)

## String over wstring
Because the scene is saved in binary format, writing both string and wstring is hard.
if wfstream is used instead of normal stream you alsways save 2(wchar_t) bytes instead of 1.
This gave a lot of porblems when writing int (some ints do not work) and you are also unable to save a byte.
for these 2 reason I made sure that every string saved in a component is a normal one so it can be read easly.

## SceneObject and Transform component
Every SceneObject can have several types of components and duplicate components, not every component needs to be on the sceneObject.
This is different for the Transform component, every sceneobject has a unique transform component.
This component is stored seperatly. I did this because 99% of all the objects needs a transform and also because this component is referenced by other components a lot it makes sence to store this on his own (other components can still be found but these arr all in an array and take a bit longer to find).
