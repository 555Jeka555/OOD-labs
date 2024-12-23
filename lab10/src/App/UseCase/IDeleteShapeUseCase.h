#ifndef LAB10_IDELETESHAPEUSECASE_H
#define LAB10_IDELETESHAPEUSECASE_H

class IDeleteShapeUseCase
{
public:

    virtual void Execute() = 0;

    ~IDeleteShapeUseCase() = default;
};

#endif //LAB10_IDELETESHAPEUSECASE_H
