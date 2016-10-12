
#include "nativelib.h"

const char* INVALID_KEY = "Invalid Key";
/**
 * This does make the assumption we have two environments:  production and everything else.
 */
char* fetchValue(char *key, char *deployEnv) {

    bool isProd = false;

    if(strcmp(deployEnv, "prod") == 0) {
        isProd = true;
    }


    if( strcmp(key, "Secret1") == 0) {
       return  isProd ?  "MySecretOneProd"  : "MySecretOne";
    } else if( strcmp(key, "Secret2") == 0) {
        return  isProd ?  "MySecretTwoProd"  : "MySecretTwo";
    } else if( strcmp(key, "Secret3") == 0) {
        return  isProd ?  "MySecretThreeProd"  : "MySecretThree";
    }  else if( strcmp(key, "Secret4") == 0) {
        return  isProd ?  "MySecretFourProd"  : "MySecretFour";
    }
    return INVALID_KEY;
}

jstring Java_net_aucutt_secrettaco_MainActivity_lookupKey(JNIEnv* env, jobject thisObj, jstring key, jstring deployEnv ) {

    if( key ==  NULL || deployEnv == NULL ) {
        return (*env)->NewStringUTF(env, INVALID_KEY);
    }

    const char *nativeKey = (*env)->GetStringUTFChars(env, key, NULL);
    const char *nativeEnv = (*env)->GetStringUTFChars(env, deployEnv, NULL);
    char *endResult;

    char* result =  fetchValue(nativeKey, nativeEnv);
    endResult = malloc(sizeof(result));
    strcpy(endResult, result);

    (*env)->ReleaseStringChars(env, key, nativeKey);
    (*env)->ReleaseStringChars(env, deployEnv, nativeEnv);

    return (*env)->NewStringUTF(env, endResult);

}


JNIEXPORT void JNICALL Java_net_aucutt_secrettaco_MainActivity_peaceTaco(JNIEnv* env,jobject thiz) {

}

//JNIEXPORT void JNICALL Java_net_aucutt_secrettaco_MainActivity_peaceTaco() {
//
//}
//
//JNIEXPORT void JNICALL Java_net_aucutt_secrettaco_MainActivity_peaceTaco(JNIEnv* env) {
//
//}


//const char *nativeKey = (*env)->GetStringUTFChars(env, key, NULL);
//char* result;
//char *endResult;
//if (NULL == key) {
//result = malloc(sizeof(INVALID));
//strcpy(result,INVALID);
//} else if (strcmp(nativeKey,SECRET_ONE )==0) {
////result = malloc(sizeof(ONE_VALUE));
////strcpy(result,ONE_VALUE);
//result = ONE_VALUE;
//} else if (strcmp(nativeKey,SECRET_TWO )==0) {
//result = malloc(sizeof(TWO_VALUE));
//strcpy(result,TWO_VALUE);
//} else if (strcmp(nativeKey,SECRET_THREE )==0) {
//result = malloc(sizeof(THREE_VALUE));
//strcpy(result,THREE_VALUE);
//} else if (strcmp(nativeKey,SECRET_FOUR )==0) {
//result = malloc(sizeof(FOUR_VALUE));
//strcpy(result,FOUR_VALUE);
//} else if (strcmp(nativeKey,SECRET_FIVE )==0) {
//result = malloc(sizeof(FIVE_VALUE));
//strcpy(result,FIVE_VALUE);
//} else  {
//result = malloc(sizeof(INVALID));
//strcpy(result,INVALID);
//}
//endResult = malloc(sizeof(result));
//strcpy(endResult,result);