#pragma once
#include "types.h"
#include "ImageStitcher.h"

#include "esutil.h"

#include <vector>
#include <memory>


class VertexBuilder;
class TexMapBuilder;
class MapPointsBuilder;
class MaskMaker;
class ColorCorrector;

class GLStitcher: public ImageStitcher
{
public:
	GLStitcher();
	~GLStitcher();
	virtual int StitchImage(VideoFrame_t *pSrcImgs, VideoFrame_t *pDstImg);
private:
	void InitGlut(const char * title = 0);
	bool InitGlModel();
	void InitShader();
	bool Initialize();
	void Release();
	virtual void Display();
	virtual void Reshape(int width, int height);
	void InitDrawOrder();
	int ReadParameters(const char *filename, FishEyeStitcherParam_t& param);
	int InitParams();

	GLuint       m_hVertShader;  // Vertex shader handle
	GLuint       m_hFragShader;  // Fragment shader handle
	GLuint       m_hTexture;  // Texture handles


	GLuint       m_hFBO;      // Handles for Frame Buffer Objects
	unsigned int m_FrameCount;
	unsigned int m_FramesPerSecond;
	unsigned int m_CurrentFBO;

	// Shader programs and their uniform locations
	GLuint base_prog;
	GLuint vao;
	GLint  adjust_loc;

	GLuint quad_vbo;
	GLuint m_elementBuffer;

	GLuint front_tex;
	GLuint back_tex;


	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_texcoords;
	std::vector<GLfloat> m_indices;
	int m_nMapTableWidth;
	int m_nMapTableHeight;
	std::vector<GLint> count;
	std::vector<GLushort> indices;
	std::vector<const GLvoid *> first;
	int m_elementCount;

	std::shared_ptr<ImageParameters> m_pImageParameter;
	std::shared_ptr<VertexBuilder> m_pVertexBuilder;
	std::shared_ptr<MapPointsBuilder> m_pFrontMapPointsBuilder;
	std::shared_ptr<MapPointsBuilder> m_pBackMapPointsBuilder;
	std::shared_ptr<MaskMaker> m_pMaskMaker;
	std::shared_ptr<TexMapBuilder> m_pFrontTexMapBuilder;
	std::shared_ptr<TexMapBuilder> m_pBackTexMapBuilder;
	std::shared_ptr<ColorCorrector> m_pColorCorrector;
	VideoFrame_t * m_pSrcImgs;
	ESContext esContext;

};

