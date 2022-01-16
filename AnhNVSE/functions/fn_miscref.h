#pragma once

DEFINE_COMMAND_PLUGIN(UpdateTubeMesh, "", 1, 5, kParams_OneString_OneInt_ThreeArrays);

#if RUNTIME
bool Cmd_UpdateTubeMesh_Execute(COMMAND_ARGS) {
	*result = 0;
	char boneName[0x40];
	int numPoints;
	UInt32 arrID1, arrID2, arrID3;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &boneName, &numPoints, &arrID1, &arrID2, &arrID3)) {
		NVSEArrayVar* srcArr1 = g_arrInterface->LookupArrayByID(arrID1);
		NVSEArrayVar* srcArr2 = g_arrInterface->LookupArrayByID(arrID2);
		NVSEArrayVar* srcArr3 = g_arrInterface->LookupArrayByID(arrID3);
		Vector3 v1, v2, v3, newVec;
		NiVector3 vF;
		NVSEArrayElement* elements = new NVSEArrayElement[3];
		g_arrInterface->GetElements(srcArr1, elements, NULL);
		v1.x = elements[0].Number();
		v1.y = elements[1].Number();
		v1.z = elements[2].Number();

		g_arrInterface->GetElements(srcArr2, elements, NULL);
		v2.x = elements[0].Number();
		v2.y = elements[1].Number();
		v2.z = elements[2].Number();

		g_arrInterface->GetElements(srcArr3, elements, NULL);
		v3.x = elements[0].Number();
		v3.y = elements[1].Number();
		v3.z = elements[2].Number();

		for (int i = 1; i < numPoints; i++) {
			newVec = V3Lerp((V3Lerp(v1, v2, (float)i / numPoints)), (V3Lerp(v2, v3, (float)i / numPoints)), (float)i / numPoints);
			std::string tempStr = boneName;
			tempStr.append(std::to_string(i));
			NiAVObject* niBlock = GetNifBlock(thisObj, 0, tempStr.data());
			vF.x = newVec.x;
			vF.y = newVec.y;
			vF.z = newVec.z;
			niBlock->LocalTranslate() = vF;
			niBlock->Update();
		}
		
		delete[] elements;
	}
	return true;
}

#endif