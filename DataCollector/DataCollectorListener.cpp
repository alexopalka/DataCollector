#include "DataCollectorListener.h"
#include "stdafx.h"


void DataCollectorListener::onInit(const Controller& controller) {
	std::cout << "Initialized" << std::endl;
}

void DataCollectorListener::onConnect(const Controller& controller) {
	std::cout << "Connected" << std::endl;

}

void DataCollectorListener::onDisconnect(const Controller& controller) {
	//Note: not dispatched when running in a debugger.
	std::cout << "Disconnected" << std::endl;
}

void DataCollectorListener::onExit(const Controller& controller) {
	std::cout << "Exited" << std::endl;
}

void DataCollectorListener::onFrame(const Controller& controller) {
	// Get the most recent frame and report some basic information
	const Frame frame = controller.frame();
	const FingerList fingers = frame.fingers();
	HandList organizedHands;
	FingerList organizedFingers;
	Hand lHand;
	Hand rHand;
	Finger lPinkie;
	Finger lIndex;
	Finger lMiddle;
	Finger lPointer;
	Finger rThumb;
	Finger rPointer;
	Finger rMiddle;
	Finger rIndex;
	Finger rPinkie;

	// Only pull data when the data exists
	if(!fingers.empty())
	{
		// Only Pull data when 10 fingers are detected
		if(!fingers.count()==10)
		{
			// Grab LeftMost Finger and set that as lPinkie
			lPinkie = fingers.leftmost();
			// Grab RightMost Finger and set that as rPinkie
			rPinkie = fingers.rightmost();
			// Now heres where it gets tricky, we need to get each hand
			// and pull rightmost from that hand.

			// This is the hand associated to lPinkie
			lHand = lPinkie.hand();

			// This is the hand associated to RPinkie
			rHand = rPinkie.hand();

			// Now get the fingers associated with each hand
			const FingerList lHandFingers = lHand.fingers();
			const FingerList rHandFingers = rHand.fingers();

			// Now get the Thumb associated with left hand
			lThumb = lHandFingers.rightmost();

			// Now get the Thumb associated with the right hand
			rThumb = rHandFingers.leftmost();

			// Now get the Middle finger Associted with Left Hand
			lMiddle = lHandFingers.frontmost();

			// Now get the Middle Finger associated with Right Hand
			rMiddle = rHandFingers.frontmost();

			// Now we need to classify the remaining 2 fingers for each hand
			// we can do this by creating list of remaining fingers
			// and checking if the position is greater  the other 
			// if its greater then that finger is on to the right on the hand 

			// Now get List of remaining left hand fingers
			const FingerList remainingLeftHandFingers;
			int i = 0;
			for(i;i < lHandFingers.count() ; i++)
			{
				if( lHandFingers[i] != lPinkie && 
					lHandFingers[i] != lMiddle &&
					lHandFingers[i] != lThumb  )
				{
					if(remainingLeftHandFingers.count() == 0)
					{
						remainingLeftHandFingers[0] = lHandFingers[i];
					}
					else
					{
						remainingLeftHandFingers[0] = lHandFingers[i];
					}
				}
			}

			// Now check if one is greater then the other
			if(remainingLeftHandFingers[0].tipPosition().x > remainingLeftHandFingers[1].tipPosition().x)
			{
				lPointer = remainingLeftHandFingers[0];
				lIndex = remainingLeftHandFingers[1];
			}
			else
			{
				lIndex = remainingLeftHandFingers[0];
				lPointer = remainingLeftHandFingers[1];
			}

			// Now get List of remaining right hand fingers
			const FingerList remainingRightHandFingers;
			int i = 0;
			for(i;i < rHandFingers.count() ; i++)
			{
				if( rHandFingers[i] != lPinkie && 
					rHandFingers[i] != lMiddle &&
					rHandFingers[i] != lThumb  )
				{
					if(remainingRightHandFingers.count() == 0)
					{
						remainingRightHandFingers[0] = rHandFingers[i];
					}
					else
					{
						remainingRightHandFingers[0] = rHandFingers[i];
					}
				}
			}

			// Now check if one is greater then the other
			if(remainingRightHandFingers[0].tipPosition().x < remainingRightHandFingers[1].tipPosition().x)
			{
				rPointer = remainingRightHandFingers[0];
				rIndex = remainingRightHandFingers[1];
			}
			else
			{
				rIndex = remainingRightHandFingers[0];
				rPointer = remainingRightHandFingers[1];
			}

			// Now we have created a whole bunch of new fingers that can be used to determine 
			// the various data we want too. 
			//For sake of organization I am going to create an organized 
			//For sake of organization I am going to create an organized 
			// list of fingers based about the fingers that we now have.
			organizedFingers[0] = lPinkie;
			organizedFingers[1] = lIndex;
			organizedFingers[2] = lMiddle;
			organizedFingers[3] = lPointer;
			organizedFingers[4] = lThumb;
			organizedFingers[5] = rThumb;
			organizedFingers[6] = rPointer;
			organizedFingers[7] = rMiddle;
			organizedFingers[8] = rIndex;
			organizedFingers[9] = rPinkie;


			// list of hands based about the 2 hands that we now have.
			// This sets other attributes from teh detected hand such as positioning 
			// and other important data
			organizedHands[0] = lHand;
			organizedHands[1] = rHand;
			// now add in the organized fingers to the specific hands;
			organizedHands[0].fingers()[0] = organizedFingers[0];
			organizedHands[0].fingers()[1] = organizedFingers[1];
			organizedHands[0].fingers()[2] = organizedFingers[2];
			organizedHands[0].fingers()[3] = organizedFingers[3];
			organizedHands[0].fingers()[4] = organizedFingers[4];
			organizedHands[1].fingers()[0] = organizedFingers[5];
			organizedHands[1].fingers()[1] = organizedFingers[6];
			organizedHands[1].fingers()[2] = organizedFingers[7];
			organizedHands[1].fingers()[3] = organizedFingers[8];
			organizedHands[1].fingers()[4] = organizedFingers[9];

			// WHEW now that we have created 2 handLists that contain the fingers
			// in order on the hand from left 2 right we can perform the necessary stuff that we want too;

			// Vector Array of Tip Positions
			Vector tipPositionVectorArraylHand[5];
			Vector tipPositionVectorArrayrHand[5];
			Vector tipPositionVectorArrayFingers[10];
			i = 0;
			for(i;i < organizedHands[0].fingers().count(); i++)
			{
				tipPositionVectorArraylHand[i] = organizedFingers[i].tipPosition();
			}
			for(i = 5;i < organizedHands[1].fingers().count(); i++)
			{
				tipPositionVectorArrayrHand[i] = organizedFingers[i].tipPosition();
			}
			i = 0;
			for(i;i < organizedFingers.count(); i++)
			{
				tipPositionVectorArrayFingers[i] = organizedFingers[i].tipPosition();
			}
			// Now that we have created 3 arrays with the finger tipPositions from left to right
			// these three arrays are the fingers of the left hand, right hand, complete list respectivly
			float xDifflHand[4];
			float xDiffrHand[4];
			float xDiffFingers[9];
			// now get x differences for Lhand
			xDifflHand[0] = (lPinkie.tipPosition().x  - lIndex.tipPosition().x)*-1;
			xDifflHand[1] = (lIndex.tipPosition().x   - lMiddle.tipPosition().x)*-1;
			xDifflHand[2] = (lMiddle.tipPosition().x  - lPointer.tipPosition().x)*-1;
			xDifflHand[3] = (lPointer.tipPosition().x - lThumb.tipPosition().x)*-1;
			// now get x differences for rhand
			xDiffrHand[0] = (rThumb.tipPosition().x  - rPointer.tipPosition().x)*-1;
			xDiffrHand[1] = (rPointer.tipPosition().x   - rMiddle.tipPosition().x)*-1;
			xDiffrHand[2] = (rMiddle.tipPosition().x  - rIndex.tipPosition().x)*-1;
			xDiffrHand[3] = (rIndex.tipPosition().x - rPinkie.tipPosition().x)*-1;
			// now get the x difference for both hands
			xDiffFingers[0] = (lPinkie.tipPosition().x  - lIndex.tipPosition().x)*-1;
			xDiffFingers[1] = (lIndex.tipPosition().x   - lMiddle.tipPosition().x)*-1;
			xDiffFingers[2] = (lMiddle.tipPosition().x  - lPointer.tipPosition().x)*-1;
			xDiffFingers[3] = (lPointer.tipPosition().x - lThumb.tipPosition().x)*-1;
			xDiffFingers[4] = (rThumb.tipPosition().x  - rPointer.tipPosition().x)*-1;
			xDiffFingers[5] = (rPointer.tipPosition().x   - rMiddle.tipPosition().x)*-1;
			xDiffFingers[6] = (rMiddle.tipPosition().x  - rIndex.tipPosition().x)*-1;
			xDiffFingers[7] = (rIndex.tipPosition().x - rPinkie.tipPosition().x)*-1;

			// x-Difference calculated now we need to calcualte 
			// the anges between all the fingers. 
		}
	}
}

void DataCollectorListener::onFocusGained(const Controller& controller) {
	std::cout << "Focus Gained" << std::endl;
}

void DataCollectorListener::onFocusLost(const Controller& controller) {
	std::cout << "Focus Lost" << std::endl;
}
