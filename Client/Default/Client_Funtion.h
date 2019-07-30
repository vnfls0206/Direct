#ifndef Client_Funtion_h__
#define Client_Funtion_h__

template <typename T>
eDirection Get_Direction(T bVector, T tVector)
{
	float Increase_X = tVector.x - bVector.x;
	float Increase_Y = tVector.y - bVector.y;

	//기울기는 (y 증가량) / (x 증가량) 이다!
	if (Increase_X > 0 && Increase_Y > 0)    //(+, +) 의경우
	{
		if ((Increase_Y / Increase_X) <= 1) return eRIGHT;
		//해당좌표의 기울기가 1보다 작을경우  (Right에 해당한다)
		if ((Increase_Y / Increase_X) > 1) return eUP;
		//해당좌표의 기울기가 1보다 클경우  (Up에 해당한다)

	}
	else if (Increase_X > 0 && Increase_Y < 0)    //(+, -) 의경우
	{
		if ((Increase_Y / Increase_X) <= -1) return eDOWN;
		//해당좌표의 기울기가 -1보다 작을경우  (Down에 해당한다)

		if ((Increase_Y / Increase_X) > -1) return eRIGHT;
		//해당좌표의 기울기가 -1보다 클경우  (Right에 해당한다)

	}
	else if (Increase_X < 0 && Increase_Y > 0)    //(-, +) 의경우
	{
		if ((Increase_Y / Increase_X) <= -1) return eUP;
		//해당좌표의 기울기가 -1보다 작을경우  (up에 해당한다)

		if ((Increase_Y / Increase_X) > -1) return eLEFT;
		//해당좌표의 기울기가 -1보다 클경우  (Left에 해당한다)

	}
	else if (Increase_X < 0 && Increase_Y < 0)    //(-, -) 의경우
	{
		if ((Increase_Y / Increase_X) <= 1) return eLEFT;
		//해당좌표의 기울기가 1보다 작을경우  (Left에 해당한다)

		if ((Increase_Y / Increase_X) > 1) return eDOWN;
		//해당좌표의 기울기가 1보다 클경우  (Down에 해당한다)

	}

}

template <typename T>
float Get_Distance(T bVector, T tVector)
{
	return  sqrt((bVector.x - tVector.x) * (bVector.x - tVector.x)
			   + (bVector.y - tVector.y) * (bVector.y - tVector.y));	//피타고라스로 거리구함
}





#endif