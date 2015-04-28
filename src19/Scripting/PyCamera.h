#ifndef PYCAMERA_INCLUDED
#define PYCAMERA_INCLUDED




PyObject * Python::PyIrr_SetCamera(PyObject * self,PyObject * args) //active camera
{
camera->setPosition(vector3df(0,0,0));
Py_RETURN_NONE;
}
PyObject * Python::PyIrr_GetCamera(PyObject * self,PyObject * args)
{
//camera->getPosition(vector3df(0,0,0));
//pyreturn(buildargs etc...
}

#endif // PYCAMERA_INCLUDED
