cbuffer W : register(b0)
{
    matrix world;
}

cbuffer V : register(b1)
{
    matrix view;
    matrix invView;
}
cbuffer P : register(b2)
{
    matrix projection;
}

struct KeyFrame
{
    int clip;
    
    uint curFrame;
    uint nextFrame;
    
    float time;
    float runningTime;
    
    float speed;
    
    float2 padding;
};

struct TweenFrame
{
    float takeTime;
    float tweenTime;
    float runningTime;
    float padding;
    
    KeyFrame cur;
    KeyFrame next;
};

#define MAX_MODEL_INSTANCE 500

cbuffer Frame : register(b4)
{
    TweenFrame tweenFrame[MAX_MODEL_INSTANCE];
}

cbuffer Type : register(b5)
{
    int modelType;
}


// 시간 버퍼 9 번에 세팅!!
cbuffer TimeBuffer : register(b9)
{
    float time;
}

Texture2DArray transformMap : register(t0);


////////////////////////////
// VertexType들 
////////////////////////////

struct VertexUV
{
    float4 pos : Position;
    float2 uv : UV;
};

struct VertexInstance
{
    float4 pos : Position;
    float2 uv : UV;
    float3 normal : Normal;
    float3 tangent : Tangent;
    float4 indices : BlendIndices;
    float4 weights : BlendWeights;
    
    matrix transform : Instance;
    uint instanceID : SV_InstanceID;
};

///////////////////////////////
// 함수 
///////////////////////////////

matrix SkinWorld(uint instanceID, float4 indices, float4 weights)
{
    matrix boneWorld = 0;
    matrix cur = 0, curAnim = 0;
    matrix next = 0, nextAnim = 0;
    
    int clip[2];
    uint curFrame[2];
    uint nextFrame[2];
    float time[2];
    
    clip[0] = tweenFrame[instanceID].cur.clip;
    curFrame[0] = tweenFrame[instanceID].cur.curFrame;
    nextFrame[0] = tweenFrame[instanceID].cur.nextFrame;
    time[0] = tweenFrame[instanceID].cur.time;
    
    clip[1] = tweenFrame[instanceID].next.clip;
    curFrame[1] = tweenFrame[instanceID].next.curFrame;
    nextFrame[1] = tweenFrame[instanceID].next.nextFrame;
    time[1] = tweenFrame[instanceID].next.time;
    
    float4 c0, c1, c2, c3;
    float4 n0, n1, n2, n3;
    
    [unroll(4)]
    for (int i = 0; i < 4; i++)
    {
        c0 = transformMap.Load(int4(indices[i] * 4 + 0, curFrame[0], clip[0], 0));
        c1 = transformMap.Load(int4(indices[i] * 4 + 1, curFrame[0], clip[0], 0));
        c2 = transformMap.Load(int4(indices[i] * 4 + 2, curFrame[0], clip[0], 0));
        c3 = transformMap.Load(int4(indices[i] * 4 + 3, curFrame[0], clip[0], 0));
        cur = matrix(c0, c1, c2, c3);
        
        n0 = transformMap.Load(int4(indices[i] * 4 + 0, nextFrame[0], clip[0], 0));
        n1 = transformMap.Load(int4(indices[i] * 4 + 1, nextFrame[0], clip[0], 0));
        n2 = transformMap.Load(int4(indices[i] * 4 + 2, nextFrame[0], clip[0], 0));
        n3 = transformMap.Load(int4(indices[i] * 4 + 3, nextFrame[0], clip[0], 0));
        next = matrix(n0, n1, n2, n3);

        // 보간
        curAnim = lerp(cur, next, time[0]);
        
        [flatten]
        if (clip[1] > -1)
        {
            c0 = transformMap.Load(int4(indices[i] * 4 + 0, curFrame[1], clip[1], 0));
            c1 = transformMap.Load(int4(indices[i] * 4 + 1, curFrame[1], clip[1], 0));
            c2 = transformMap.Load(int4(indices[i] * 4 + 2, curFrame[1], clip[1], 0));
            c3 = transformMap.Load(int4(indices[i] * 4 + 3, curFrame[1], clip[1], 0));
            cur = matrix(c0, c1, c2, c3);
        
            n0 = transformMap.Load(int4(indices[i] * 4 + 0, nextFrame[1], clip[1], 0));
            n1 = transformMap.Load(int4(indices[i] * 4 + 1, nextFrame[1], clip[1], 0));
            n2 = transformMap.Load(int4(indices[i] * 4 + 2, nextFrame[1], clip[1], 0));
            n3 = transformMap.Load(int4(indices[i] * 4 + 3, nextFrame[1], clip[1], 0));
            next = matrix(n0, n1, n2, n3);
            
            // 보간
            nextAnim = lerp(cur, next, time[1]);
            
            curAnim = lerp(curAnim, nextAnim, tweenFrame[instanceID].tweenTime);
        }
        
        boneWorld += mul(weights[i], curAnim);
    }
    
    return boneWorld;
}