#ifndef OSISDATAIF
#define OSISDATAIF

class OsisDataIf
{
public:
   virtual void DataInd(class QByteArray& qba) = 0;
};

#endif // OSISDATAIF

