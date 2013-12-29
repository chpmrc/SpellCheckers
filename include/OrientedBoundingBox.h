#ifndef ORIENTEDBOUNDINGBOX_H
#define ORIENTEDBOUNDINGBOX_H


class OrientedBoundingBox
{
    public:
        OrientedBoundingBox(float radius);
        virtual ~OrientedBoundingBox();

        bool collidesWith(OrientedBoundingBox *otherObb, float distance);
    protected:
        // TODO First implementation is with sphere
        float radius;
    private:
};

#endif // ORIENTEDBOUNDINGBOX_H
