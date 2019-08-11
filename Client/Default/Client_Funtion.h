#ifndef Client_Funtion_h__
#define Client_Funtion_h__

template <typename T>
eDirection Get_Direction(T bVector, T tVector)
{
	float Increase_X = tVector.x - bVector.x;
	float Increase_Y = tVector.y - bVector.y;

	//����� (y ������) / (x ������) �̴�!
	if (Increase_X > 0 && Increase_Y > 0)    //(+, +) �ǰ��
	{
		if ((Increase_Y / Increase_X) <= 1) return eRIGHT;
		//�ش���ǥ�� ���Ⱑ 1���� �������  (Right�� �ش��Ѵ�)
		if ((Increase_Y / Increase_X) > 1) return eUP;
		//�ش���ǥ�� ���Ⱑ 1���� Ŭ���  (Up�� �ش��Ѵ�)

	}
	else if (Increase_X > 0 && Increase_Y < 0)    //(+, -) �ǰ��
	{
		if ((Increase_Y / Increase_X) <= -1) return eDOWN;
		//�ش���ǥ�� ���Ⱑ -1���� �������  (Down�� �ش��Ѵ�)

		if ((Increase_Y / Increase_X) > -1) return eRIGHT;
		//�ش���ǥ�� ���Ⱑ -1���� Ŭ���  (Right�� �ش��Ѵ�)

	}
	else if (Increase_X < 0 && Increase_Y > 0)    //(-, +) �ǰ��
	{
		if ((Increase_Y / Increase_X) <= -1) return eUP;
		//�ش���ǥ�� ���Ⱑ -1���� �������  (up�� �ش��Ѵ�)

		if ((Increase_Y / Increase_X) > -1) return eLEFT;
		//�ش���ǥ�� ���Ⱑ -1���� Ŭ���  (Left�� �ش��Ѵ�)

	}
	else if (Increase_X < 0 && Increase_Y < 0)    //(-, -) �ǰ��
	{
		if ((Increase_Y / Increase_X) <= 1) return eLEFT;
		//�ش���ǥ�� ���Ⱑ 1���� �������  (Left�� �ش��Ѵ�)

		if ((Increase_Y / Increase_X) > 1) return eDOWN;
		//�ش���ǥ�� ���Ⱑ 1���� Ŭ���  (Down�� �ش��Ѵ�)

	}

}

template <typename T>
float Get_Distance(T bVector, T tVector)
{
	return  sqrt((bVector.x - tVector.x) * (bVector.x - tVector.x)
			   + (bVector.y - tVector.y) * (bVector.y - tVector.y));	//��Ÿ��󽺷� �Ÿ�����
}

template <typename T>
void Clear_List(T List)
{
	while (!List.empty())
	{
		auto iter = List.begin();
		delete[](*iter);
		List.erase(iter);
	}
}




#endif