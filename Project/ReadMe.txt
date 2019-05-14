19.05.14
./Camera/CameraBase
./Render/RenderManager
./Object/Object
일단 기초로 만들었습니다
./Object 아래 ObjectManager도 추가할 예정

19.05.09
./Render/Shader에 특정 shader만 set 할 수 있도록 설정하기

19.05.06
./Render/Shader에 ShaderManager에 AddShaderProcess 추가했습니다, 파일 이름, 추가할 쉐이더 단계, 함수 이름 전달받으면 해당하는 shader가 있는지 확인후 만들어줍니다
./Common.h에 Shader에 전달할 Vertex 정보들 구조체 넣어뒀습니다.

19.05.04
오늘은 아무 것도 안했습니다
./Render/Shader에 대해서, 그냥 쉐이더 함수 다른 이름이면 새로 파일 만드는걸로 고려를...

19.05.03
프레임워크 새로 짜는 중입니다.
../_Includes : 필요한 외부 헤더파일입니다. 현재 DXInc만 있습니다.
../_Libraries : 필요한 외부 라이브러리입니다. 현재 DXLib만 있습니다.
DirectXTex도 위 폴더들에 들어있습니다.

Root
Common.h : 전반적으로 쓰일 클래스나 네임스페이스등을 위해 만들었습니다. 현재 Common::Singleton만 있습니다.
stdafx : 프로그램 전반적으로 쓰일 헤더파일 혹은 라이브러리를 미리 선언해놓는 곳입니다.
Project.cpp : 프로젝트 시작점입니다. 싱글톤을 미리 만들어두거나 종료시점에 destroy하기도 합니다.

System
Windows : 실질적인 프로그램 시작점입니다, 윈도우창의 생성, 위치 조정, 매 프레임마다의 작동, 입력처리 등에 대해 가지고 있습니다.
D3D : DirectX11을 이용하기 위해 필요한 기본 설정및 device, deviceContext등을 생성합니다.
InputManager : 휠 입력 발생 시에는 Windows의 WndProc에서 InputManager의 InputProc으로 들어오고 일반적인 키입력은 Frame에서 처리하게 됩니다.
TimeManager : 프로그램 시작 후에 경과 시간등에 대해서 관리하는 클래스입니다.

Render
Shader : ShaderBuffer, Shader, ShaderManager가 같이 들어가 있습니다. ShaderBuffer는 hlsl의 constant buffer에 전달할 데이터를 담아놓는 클래스고, Shader는 실질적인 Shader를 setting하거나 하는 부분이고, ShaderManager는 그런 Shader들을 map으로 관리합니다. *수정필요, shaderFile, reflection, inputLayout을 제외한 나머지는 vector나 map으로 할 필요 있음
States : rasterizer, depth stencil, sampler, blend state의 대한 base description을 가지고 있다가 요청하면 전달하는 역할도 하고, 주어진 desc로 state를 만들어서 돌려주거나 합니다.