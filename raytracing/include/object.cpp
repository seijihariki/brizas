class Object {
public:
    Object (Material &material);

private:
    virtual glm::vec3 intersects (glm::vec3 start, glm::vec3 direction);

    Material &material;
};
