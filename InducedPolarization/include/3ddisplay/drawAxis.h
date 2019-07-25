#pragma once
#include <osg/Array>
#include <osg/Group>

namespace osgEngine
{
	class cDrawAxis
	{
	public:
		cDrawAxis() 
		{
			step = 2.0;
			m_tapValue = 3;
			m_xMin = (std::numeric_limits<double>::min)();
			m_yMin = (std::numeric_limits<double>::min)();
			m_zMin = (std::numeric_limits<double>::min)();
			m_xMax = (std::numeric_limits<double>::max)();
			m_yMax = (std::numeric_limits<double>::max)();
			m_zMax = (std::numeric_limits<double>::max)();
			m_AxisNode = new osg::Group;
		}
		~cDrawAxis() 
		{
		}

		osg::ref_ptr<osg::Group> drawAxis(int minRx, int maxRx,int minRy,int maxRy, int minRz, int maxRz)
		{

			drawQuard(minRx, maxRx, minRy, maxRy, minRz, maxRz);
			drawXAxis(minRx, maxRx, minRy, maxRy, minRz, maxRz);
			drawYAxis(minRx, maxRx, minRy, maxRy, minRz, maxRz);
			drawZAxis(minRx, maxRx, minRy, maxRy, minRz, maxRz);

			return m_AxisNode.get();
		}

		void drawQuard(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
		void drawXAxis(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
		void drawYAxis(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
		void drawZAxis(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);

	private:
		float m_xMin;
		float m_yMin;
		float m_zMin;
		float m_xMax;
		float m_yMax;
		float m_zMax;
		float step;
		int m_tapValue;
		osg::ref_ptr<osg::Group> m_AxisNode;
	};
};