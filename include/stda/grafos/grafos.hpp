

#ifndef GRAFOSSTD
#define GRAFOSSTD
/* @Documentacion:
 * Este archivo debe contener la clase para manejar los grafos de cualquier tipo de dato
 * Por ahora esta clase no es capaz de cumplir estas espectativas por lo que se esta dessarrollando la manera de lograrlo
*/
template <typename T>
class grafos
{
private:
    T data;
    size_t id;
    bool visited;
    grafos **vertex;

public:
    grafos(T b) {}
};

#endif