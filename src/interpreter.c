/**
 * interprets the tree
 */

typedef struct {
    environment;  // in this case function variable bindings
    expressions;
} Closure;

Closure evaluate(Closure closure);

void interpret(ExpressionWp setup) {
    ObjWP   objects = []
    ClassWP classes = []

    for exp in setup {
        OBJ -> insert objects
        CLASS -> insert classes
    }

    while (objects.count > 0) {
        for obj in objects {
            if (obj.sleeping > 0) { obj.sleeping-- ;continue;}
            while (obj.count > 0) {
                Function receive = classes[obj.id].funcs[0]
                Closure op = {env, newWP(receive)}
                res = evaluate(op)
            }
        }
    }
}
