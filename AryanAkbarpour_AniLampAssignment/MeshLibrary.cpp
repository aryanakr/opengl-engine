#include "MeshLibrary.h"


std::vector<float> MeshLibrary::getUnitCircleVertices(int sectorCount)
{
    const float PI = 3.1415926f;
    float sectorStep = 2 * PI / sectorCount;
    float sectorAngle;  // radian

    std::vector<float> unitCircleVertices;
    for (int i = 0; i <= sectorCount; ++i)
    {
        sectorAngle = i * sectorStep;
        unitCircleVertices.push_back(cos(sectorAngle)); // x
        unitCircleVertices.push_back(0);                // z
        unitCircleVertices.push_back(sin(sectorAngle)); // y
    }
    return unitCircleVertices;
}

Mesh MeshLibrary::cylinderMesh( float bottomRadius, float topRadius, float height, int sectorCount) {
    // get unit circle vectors on XY-plane
    std::vector<float> unitVertices = getUnitCircleVertices(sectorCount);

    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    float radius;
    // put side vertices to vertices array
    for (int i = 0; i < 2; ++i)
    {
        if (i == 0) {
            radius = bottomRadius;
        }
        else
        {
            radius = topRadius;
        }
        float h = i * height;           // z value; -h/2 to h/2
        float t = 1.0f - i;                              // vertical tex coord; 1 to 0

        for (int j = 0, k = 0; j <= sectorCount; ++j, k += 3)
        {
            Vertex vertex;
            glm::vec3 vector;

            float ux = unitVertices[k];
            float uy = unitVertices[k + 1];
            float uz = unitVertices[k + 2];
            // position vector
            vector.x = ux * radius;
            vector.y = h;
            vector.z = uz * radius;
            vertex.position = vector;
            // normal vector
            vector.x = ux;
            vector.y = uy;
            vector.z = uz;
            vertex.normal = vector;

            glm::vec2 vec;
            vec.x = (float)j / sectorCount;
            vec.y = t;
            vertex.texCoords = vec;

            vertices.push_back(vertex);
        }
    }

    // the starting index for the base/top surface
    int baseCenterIndex = (int)vertices.size();
    int topCenterIndex = baseCenterIndex + sectorCount + 1; // include center vertex

    // put base and top vertices to vertices arrays
    for (int i = 0; i < 2; ++i)
    {
        if (i == 0) {
            radius = bottomRadius;
        }
        else
        {
            radius = topRadius;
        }
        Vertex centreVertex;
        glm::vec3 centreVector;

        float h =  i * height;           // z value; -h/2 to h/2
        float nh = -1 + i * 2;                           // z value of normal; -1 to 1

        // center point
        // position vector
        centreVector.x = 0;
        centreVector.y = h;
        centreVector.z = 0;
        centreVertex.position = centreVector;
        // normal vector
        centreVector.x = 0;
        centreVector.y = nh;
        centreVector.z = 0;
        centreVertex.normal = centreVector;

        glm::vec2 centreTexvVec;
        centreTexvVec.x = 0.5f;
        centreTexvVec.y = 0.5f;
        centreVertex.texCoords = centreTexvVec;
        vertices.push_back(centreVertex);

        for (int j = 0, k = 0; j < sectorCount; ++j, k += 3)
        {
            Vertex vertex;
            glm::vec3 vector;

            float ux = unitVertices[k];
            float uz = unitVertices[k + 2];

            // position vector
            vector.x = ux * radius;
            vector.y = h;
            vector.z = uz * radius;
            vertex.position = vector;
            // normal vector
            vector.x = 0;
            vector.y = nh;
            vector.z = 0;
            vertex.normal = vector;

            glm::vec2 vec;
            vec.x = -ux * 0.5f + 0.5f;
            vec.y = -uz * 0.5f + 0.5f;
            vertex.texCoords = vec;

            vertices.push_back(vertex);
        }
    }

    // Calculating indices
    int k1 = 0;
    int k2 = sectorCount + 1;

    //Side Surface indices
    for (int i = 0; i < sectorCount; ++i, ++k1, ++k2)
    {
        // 2 triangles per sector
        // k1 => k1+1 => k2
        indices.push_back(k1);
        indices.push_back(k1 + 1);
        indices.push_back(k2);

        // k2 => k1+1 => k2+1
        indices.push_back(k2);
        indices.push_back(k1 + 1);
        indices.push_back(k2 + 1);
    }

    // base surfacce indices
    for (int i = 0, k = baseCenterIndex + 1; i < sectorCount; ++i, ++k)
    {
        if (i < sectorCount - 1)
        {
            indices.push_back(baseCenterIndex);
            indices.push_back(k + 1);
            indices.push_back(k);
        }
        else // last triangle
        {
            indices.push_back(baseCenterIndex);
            indices.push_back(baseCenterIndex + 1);
            indices.push_back(k);
        }
    }

    // top surface indices
    for (int i = 0, k = topCenterIndex + 1; i < sectorCount; ++i, ++k)
    {
        if (i < sectorCount - 1)
        {
            indices.push_back(topCenterIndex);
            indices.push_back(k);
            indices.push_back(k + 1);
        }
        else // last triangle
        {
            indices.push_back(topCenterIndex);
            indices.push_back(k);
            indices.push_back(topCenterIndex + 1);
        }
    }

    return Mesh(vertices, indices, textures);
}

Mesh MeshLibrary::cubeMesh() {
    float cubeVertices[] = {
            -0.5f, -0.5f, -0.5f,  -1, 0, 0,  0.0f, 0.0f,  // 0
            -0.5f, -0.5f,  0.5f,  -1, 0, 0,  1.0f, 0.0f,  // 1
            -0.5f,  0.5f, -0.5f,  -1, 0, 0,  0.0f, 1.0f,  // 2
            -0.5f,  0.5f,  0.5f,  -1, 0, 0,  1.0f, 1.0f,  // 3
            0.5f, -0.5f, -0.5f,   1, 0, 0,  1.0f, 0.0f,  // 4
            0.5f, -0.5f,  0.5f,   1, 0, 0,  0.0f, 0.0f,  // 5
            0.5f,  0.5f, -0.5f,   1, 0, 0,  1.0f, 1.0f,  // 6
            0.5f,  0.5f,  0.5f,   1, 0, 0,  0.0f, 1.0f,  // 7

            -0.5f, -0.5f, -0.5f,  0,0,-1,  1.0f, 0.0f,  // 8
            -0.5f, -0.5f,  0.5f,  0,0,1,   0.0f, 0.0f,  // 9
            -0.5f,  0.5f, -0.5f,  0,0,-1,  1.0f, 1.0f,  // 10
            -0.5f,  0.5f,  0.5f,  0,0,1,   0.0f, 1.0f,  // 11
            0.5f, -0.5f, -0.5f,  0,0,-1,  0.0f, 0.0f,  // 12
            0.5f, -0.5f,  0.5f,  0,0,1,   1.0f, 0.0f,  // 13
            0.5f,  0.5f, -0.5f,  0,0,-1,  0.0f, 1.0f,  // 14
            0.5f,  0.5f,  0.5f,  0,0,1,   1.0f, 1.0f,  // 15

            -0.5f, -0.5f, -0.5f,  0,-1,0,  0.0f, 0.0f,  // 16
            -0.5f, -0.5f,  0.5f,  0,-1,0,  0.0f, 1.0f,  // 17
            -0.5f,  0.5f, -0.5f,  0,1,0,   0.0f, 1.0f,  // 18
            -0.5f,  0.5f,  0.5f,  0,1,0,   0.0f, 0.0f,  // 19
            0.5f, -0.5f, -0.5f,  0,-1,0,  1.0f, 0.0f,  // 20
            0.5f, -0.5f,  0.5f,  0,-1,0,  1.0f, 1.0f,  // 21
            0.5f,  0.5f, -0.5f,  0,1,0,   1.0f, 1.0f,  // 22
            0.5f,  0.5f,  0.5f,  0,1,0,   1.0f, 0.0f   // 23
    };
    int cubeIndices[] = {
            0,1,3, // x -ve 
            3,2,0, // x -ve
            4,6,7, // x +ve
            7,5,4, // x +ve
            9,13,15, // z +ve
            15,11,9, // z +ve
            8,10,14, // z -ve
            14,12,8, // z -ve
            16,20,21, // y -ve
            21,17,16, // y -ve
            23,22,18, // y +ve
            18,19,23  // y +ve
    };

    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    for (unsigned int i = 0; i < 24; i++)
    {
        Vertex vertex;
        // process vertex positions, normals and texture coordinates
        glm::vec3 vector;
        vector.x = cubeVertices[i * 8];
        vector.y = cubeVertices[i * 8 + 1];
        vector.z = cubeVertices[i * 8 + 2];
        vertex.position = vector;

        vector.x = cubeVertices[i * 8 + 3];
        vector.y = cubeVertices[i * 8 + 4];
        vector.z = cubeVertices[i * 8 + 5];
        vertex.normal = vector;

        glm::vec2 vec;
        vec.x = cubeVertices[i * 8 + 6];
        vec.y = cubeVertices[i * 8 + 7];
        vertex.texCoords = vec;

        vertices.push_back(vertex);
    }
    for (unsigned int i = 0; i < sizeof(cubeIndices) / sizeof(cubeIndices[0]); i++)
    {
        indices.push_back(cubeIndices[i]);
    }

    return Mesh(vertices, indices, textures);
}

Mesh MeshLibrary::planeMesh()
{
    float planeVertices[] = {
            -0.5f, 0.0f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,  // top left
            -0.5f, 0.0f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,  // bottom left
             0.5f, 0.0f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  // bottom right
             0.5f, 0.0f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f   // top right
    };
    int planeIndices[] = {
            0, 1, 2,
            0, 2, 3
    };

    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    for (unsigned int i = 0; i < 4; i++)
    {
        Vertex vertex;
        // process vertex positions, normals and texture coordinates
        glm::vec3 vector;
        vector.x = planeVertices[i * 8];
        vector.y = planeVertices[i * 8 + 1];
        vector.z = planeVertices[i * 8 + 2];
        vertex.position = vector;

        vector.x = planeVertices[i * 8 + 3];
        vector.y = planeVertices[i * 8 + 4];
        vector.z = planeVertices[i * 8 + 5];
        vertex.normal = vector;

        glm::vec2 vec;
        vec.x = planeVertices[i * 8 + 6];
        vec.y = planeVertices[i * 8 + 7];
        vertex.texCoords = vec;

        vertices.push_back(vertex);
    }
    for (unsigned int i = 0; i < sizeof(planeIndices) / sizeof(planeIndices[0]); i++)
    {
        indices.push_back(planeIndices[i]);
    }

    return Mesh(vertices, indices, textures);
}

Mesh MeshLibrary::sphereMesh() {

    const float PI = 3.1415926f;
    float radius = 0.5f;
    int sectorCount = 32;
    int stackCount = 32;

    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
    float s, t;                                     // vertex texCoord
    int k1, k2;

    float sectorStep = 2 * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;

    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    // Calculate vertices
    for (int i = 0; i <= stackCount; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= sectorCount; ++j)
        {
            Vertex vertex;
            glm::vec3 vector;

            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            vector.x = x;
            vector.y = y;
            vector.z = z;
            vertex.position = vector;

            // normalized vertex normal (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            vector.x = nx;
            vector.y = ny;
            vector.z = nz;
            vertex.normal = vector;

            // vertex tex coord (s, t) range between [0, 1]
            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            glm::vec2 vec;
            vec.x = s;
            vec.y = t;
            vertex.texCoords = vec;

            vertices.push_back(vertex);
        }
    }
    // Calculate Indices
    for (int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if (i != (stackCount - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    return Mesh(vertices, indices, textures);

}
